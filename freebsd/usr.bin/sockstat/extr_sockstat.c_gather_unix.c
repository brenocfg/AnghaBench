#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xunpgen {scalar_t__ xug_gen; int xug_len; } ;
struct TYPE_4__ {scalar_t__ sun_family; } ;
struct TYPE_3__ {scalar_t__ xso_so; } ;
struct xunpcb {int xu_len; scalar_t__ unp_conn; TYPE_2__ xu_addr; int /*<<< orphan*/  xu_unpp; TYPE_1__ xu_socket; } ;
struct sockaddr_storage {int dummy; } ;
struct sock {int proto; char const* protoname; struct sock* next; scalar_t__ socket; struct addr* faddr; struct addr* laddr; scalar_t__ family; int /*<<< orphan*/  pcb; } ;
struct addr {int /*<<< orphan*/ * next; struct sockaddr_storage address; } ;
typedef  scalar_t__ kvaddr_t ;

/* Variables and functions */
 scalar_t__ AF_UNIX ; 
 scalar_t__ ENOMEM ; 
 uintptr_t HASHSIZE ; 
#define  SOCK_DGRAM 130 
#define  SOCK_SEQPACKET 129 
#define  SOCK_STREAM 128 
 int /*<<< orphan*/  abort () ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  opt_c ; 
 int /*<<< orphan*/  opt_l ; 
 scalar_t__ opt_v ; 
 void* realloc (void*,size_t) ; 
 struct sock** sockhash ; 
 scalar_t__ sysctlbyname (char const*,void*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static void
gather_unix(int proto)
{
	struct xunpgen *xug, *exug;
	struct xunpcb *xup;
	struct sock *sock;
	struct addr *laddr, *faddr;
	const char *varname, *protoname;
	size_t len, bufsize;
	void *buf;
	int hash, retry;

	switch (proto) {
	case SOCK_STREAM:
		varname = "net.local.stream.pcblist";
		protoname = "stream";
		break;
	case SOCK_DGRAM:
		varname = "net.local.dgram.pcblist";
		protoname = "dgram";
		break;
	case SOCK_SEQPACKET:
		varname = "net.local.seqpacket.pcblist";
		protoname = "seqpac";
		break;
	default:
		abort();
	}
	buf = NULL;
	bufsize = 8192;
	retry = 5;
	do {
		for (;;) {
			if ((buf = realloc(buf, bufsize)) == NULL)
				err(1, "realloc()");
			len = bufsize;
			if (sysctlbyname(varname, buf, &len, NULL, 0) == 0)
				break;
			if (errno != ENOMEM || len != bufsize)
				err(1, "sysctlbyname()");
			bufsize *= 2;
		}
		xug = (struct xunpgen *)buf;
		exug = (struct xunpgen *)(void *)
		    ((char *)buf + len - sizeof(*exug));
		if (xug->xug_len != sizeof(*xug) ||
		    exug->xug_len != sizeof(*exug)) {
			warnx("struct xinpgen size mismatch");
			goto out;
		}
	} while (xug->xug_gen != exug->xug_gen && retry--);

	if (xug->xug_gen != exug->xug_gen && opt_v)
		warnx("warning: data may be inconsistent");

	for (;;) {
		xug = (struct xunpgen *)(void *)((char *)xug + xug->xug_len);
		if (xug >= exug)
			break;
		xup = (struct xunpcb *)xug;
		if (xup->xu_len != sizeof(*xup)) {
			warnx("struct xunpcb size mismatch");
			goto out;
		}
		if ((xup->unp_conn == 0 && !opt_l) ||
		    (xup->unp_conn != 0 && !opt_c))
			continue;
		if ((sock = calloc(1, sizeof(*sock))) == NULL)
			err(1, "malloc()");
		if ((laddr = calloc(1, sizeof *laddr)) == NULL)
			err(1, "malloc()");
		if ((faddr = calloc(1, sizeof *faddr)) == NULL)
			err(1, "malloc()");
		sock->socket = xup->xu_socket.xso_so;
		sock->pcb = xup->xu_unpp;
		sock->proto = proto;
		sock->family = AF_UNIX;
		sock->protoname = protoname;
		if (xup->xu_addr.sun_family == AF_UNIX)
			laddr->address =
			    *(struct sockaddr_storage *)(void *)&xup->xu_addr;
		else if (xup->unp_conn != 0)
			*(kvaddr_t*)&(faddr->address) = xup->unp_conn;
		laddr->next = NULL;
		faddr->next = NULL;
		sock->laddr = laddr;
		sock->faddr = faddr;
		hash = (int)((uintptr_t)sock->socket % HASHSIZE);
		sock->next = sockhash[hash];
		sockhash[hash] = sock;
	}
out:
	free(buf);
}