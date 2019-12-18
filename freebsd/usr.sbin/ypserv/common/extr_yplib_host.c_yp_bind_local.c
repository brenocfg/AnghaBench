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
typedef  int /*<<< orphan*/  u_long ;
struct timeval {int tv_sec; scalar_t__ tv_usec; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int sin_len; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
typedef  int /*<<< orphan*/  CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 int RPC_ANYSOCK ; 
 int /*<<< orphan*/ * clntudp_create (struct sockaddr_in*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct timeval,int*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 

CLIENT *
yp_bind_local(u_long program, u_long version)
{
	struct sockaddr_in rsrv_sin;
	static CLIENT *client;
	struct timeval tv;
	int rsrv_sock;

	memset(&rsrv_sin, 0, sizeof rsrv_sin);
	rsrv_sin.sin_len = sizeof rsrv_sin;
	rsrv_sin.sin_family = AF_INET;
	rsrv_sin.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	rsrv_sock = RPC_ANYSOCK;

	tv.tv_sec = 10;
	tv.tv_usec = 0;

	client = clntudp_create(&rsrv_sin, program, version, tv, &rsrv_sock);
	if (client == NULL) {
		errx(1, "clntudp_create: no contact with localhost.");
	}

	return (client);
}