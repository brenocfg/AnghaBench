#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u_long ;
typedef  int u_int32_t ;
struct netconfig {int dummy; } ;
struct netbuf {int dummy; } ;
typedef  int /*<<< orphan*/  rpcvers_t ;
typedef  int /*<<< orphan*/  rpcprog_t ;
typedef  int /*<<< orphan*/  bool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int IPPROTO_TCP ; 
 int IPPROTO_UDP ; 
 struct netconfig* __rpc_getconfip (char*) ; 
 int /*<<< orphan*/  free (struct netbuf*) ; 
 int /*<<< orphan*/  freenetconfigent (struct netconfig*) ; 
 int /*<<< orphan*/  rpcb_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct netconfig*,struct netbuf*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 
 struct netbuf* uaddr2taddr (struct netconfig*,char*) ; 

bool_t
pmap_set(u_long program, u_long version, int protocol, int port)
{
	bool_t rslt;
	struct netbuf *na;
	struct netconfig *nconf;
	char buf[32];

	if ((protocol != IPPROTO_UDP) && (protocol != IPPROTO_TCP)) {
		return (FALSE);
	}
	nconf = __rpc_getconfip(protocol == IPPROTO_UDP ? "udp" : "tcp");
	if (nconf == NULL) {
		return (FALSE);
	}
	snprintf(buf, sizeof buf, "0.0.0.0.%d.%d", 
	    (((u_int32_t)port) >> 8) & 0xff, port & 0xff);
	na = uaddr2taddr(nconf, buf);
	if (na == NULL) {
		freenetconfigent(nconf);
		return (FALSE);
	}
	rslt = rpcb_set((rpcprog_t)program, (rpcvers_t)version, nconf, na);
	free(na);
	freenetconfigent(nconf);
	return (rslt);
}