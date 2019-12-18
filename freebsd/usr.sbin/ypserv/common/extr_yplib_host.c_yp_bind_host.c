#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_short ;
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  u_int32_t ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int sin_len; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct hostent {scalar_t__ h_addr; } ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int RPC_ANYSOCK ; 
 int /*<<< orphan*/ * clnttcp_create (struct sockaddr_in*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * clntudp_create (struct sockaddr_in*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval,int*) ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 struct hostent* gethostbyname (char*) ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 scalar_t__ inet_aton (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 

CLIENT *
yp_bind_host(char *server, u_long program, u_long version, u_short port,
    int usetcp)
{
	struct sockaddr_in rsrv_sin;
	static CLIENT *client;
	struct hostent *h;
	struct timeval tv;
	int rsrv_sock;

	memset(&rsrv_sin, 0, sizeof rsrv_sin);
	rsrv_sin.sin_len = sizeof rsrv_sin;
	rsrv_sin.sin_family = AF_INET;
	rsrv_sock = RPC_ANYSOCK;
	if (port != 0)
		rsrv_sin.sin_port = htons(port);

	if (*server >= '0' && *server <= '9') {
		if (inet_aton(server, &rsrv_sin.sin_addr) == 0) {
			errx(1, "inet_aton: invalid address %s.",
			    server);
		}
	} else {
		h = gethostbyname(server);
		if (h == NULL) {
			errx(1, "gethostbyname: unknown host %s.",
			    server);
		}
		rsrv_sin.sin_addr.s_addr = *(u_int32_t *)h->h_addr;
	}

	tv.tv_sec = 10;
	tv.tv_usec = 0;

	if (usetcp)
		client = clnttcp_create(&rsrv_sin, program, version,
		    &rsrv_sock, 0, 0);
	else
		client = clntudp_create(&rsrv_sin, program, version, tv,
		    &rsrv_sock);

	if (client == NULL) {
		errx(1, "clntudp_create: no contact with host %s.",
		    server);
	}

	return (client);
}