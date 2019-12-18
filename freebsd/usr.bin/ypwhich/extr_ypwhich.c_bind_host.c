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
typedef  int /*<<< orphan*/  xdrproc_t ;
struct TYPE_3__ {int /*<<< orphan*/  ypbind_binding_addr; } ;
struct TYPE_4__ {TYPE_1__ ypbind_bindinfo; } ;
struct ypbind_resp {scalar_t__ ypbind_status; TYPE_2__ ypbind_resp_u; } ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct sockaddr_in {int dummy; } ;
struct in_addr {int /*<<< orphan*/  s_addr; } ;
struct hostent {char* h_name; } ;
typedef  int /*<<< orphan*/  ss_addr ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int RPC_ANYSOCK ; 
 int RPC_SUCCESS ; 
 int /*<<< orphan*/  YPBINDPROC_DOMAIN ; 
 int /*<<< orphan*/  YPBINDPROG ; 
 int /*<<< orphan*/  YPBINDVERS ; 
 scalar_t__ YPBIND_SUCC_VAL ; 
 int YPERR_YPBIND ; 
 int clnt_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ ,struct ypbind_resp*,struct timeval) ; 
 int /*<<< orphan*/  clnt_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * clntudp_create (struct sockaddr_in*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval,int*) ; 
 struct hostent* gethostbyaddr (char*,int,int /*<<< orphan*/ ) ; 
 char* inet_ntoa (struct in_addr) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 
 scalar_t__ xdr_domainname ; 
 scalar_t__ xdr_ypbind_resp ; 
 int /*<<< orphan*/  yperr_string (int) ; 

__attribute__((used)) static int
bind_host(char *dom, struct sockaddr_in *sin)
{
	struct hostent *hent = NULL;
	struct ypbind_resp ypbr;
	struct in_addr ss_addr;
	struct timeval tv;
	CLIENT *client;
	int sock, r;

	sock = RPC_ANYSOCK;
	tv.tv_sec = 15;
	tv.tv_usec = 0;
	client = clntudp_create(sin, YPBINDPROG, YPBINDVERS, tv, &sock);

	if (client == NULL) {
		warnx("host is not bound to a ypmaster");
		return (YPERR_YPBIND);
	}

	tv.tv_sec = 5;
	tv.tv_usec = 0;

	r = clnt_call(client, YPBINDPROC_DOMAIN,
		(xdrproc_t)xdr_domainname, &dom,
		(xdrproc_t)xdr_ypbind_resp, &ypbr, tv);
	if (r != RPC_SUCCESS) {
		warnx("can't clnt_call: %s", yperr_string(YPERR_YPBIND));
		clnt_destroy(client);
		return (YPERR_YPBIND);
	} else {
		if (ypbr.ypbind_status != YPBIND_SUCC_VAL) {
			warnx("can't yp_bind: reason: %s",
			    yperr_string(ypbr.ypbind_status));
			clnt_destroy(client);
			return (r);
		}
	}
	clnt_destroy(client);

	memmove(&ss_addr.s_addr, &ypbr.ypbind_resp_u.ypbind_bindinfo.ypbind_binding_addr,
	    sizeof (ss_addr));

	hent = gethostbyaddr((char *)&ss_addr.s_addr, sizeof(ss_addr.s_addr),
	    AF_INET);
	if (hent != NULL)
		printf("%s\n", hent->h_name);
	else
		printf("%s\n", inet_ntoa(ss_addr));

	return (0);
}