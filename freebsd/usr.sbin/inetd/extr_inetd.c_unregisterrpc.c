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
typedef  scalar_t__ u_int ;
struct servtab {scalar_t__ se_socktype; scalar_t__ se_family; scalar_t__ se_checked; scalar_t__ se_rpc_prog; scalar_t__ se_rpc_lowvers; scalar_t__ se_rpc_highvers; int se_fd; scalar_t__ se_nomapped; int /*<<< orphan*/  se_proto; int /*<<< orphan*/  se_rpc; struct servtab* se_next; } ;
struct netconfig {int dummy; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  SIGBLOCK ; 
 scalar_t__ SOCK_DGRAM ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  print_service (char*,struct servtab*) ; 
 int /*<<< orphan*/  rpcb_unset (scalar_t__,scalar_t__,struct netconfig*) ; 
 struct servtab* servtab ; 
 long sigblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigsetmask (long) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct netconfig* tcp6conf ; 
 struct netconfig* tcpconf ; 
 struct netconfig* udp6conf ; 
 struct netconfig* udpconf ; 

__attribute__((used)) static void
unregisterrpc(struct servtab *sep)
{
        u_int i;
        struct servtab *sepp;
	long omask;
	struct netconfig *netid4, *netid6;

	omask = sigblock(SIGBLOCK);
	netid4 = sep->se_socktype == SOCK_DGRAM ? udpconf : tcpconf;
	netid6 = sep->se_socktype == SOCK_DGRAM ? udp6conf : tcp6conf;
	if (sep->se_family == AF_INET)
		netid6 = NULL;
	else if (sep->se_nomapped)
		netid4 = NULL;
	/*
	 * Conflict if same prog and protocol - In that case one should look
	 * to versions, but it is not interesting: having separate servers for
	 * different versions does not work well.
	 * Therefore one do not unregister if there is a conflict.
	 * There is also transport conflict if destroying INET when INET46
	 * exists, or destroying INET46 when INET exists
	 */
        for (sepp = servtab; sepp; sepp = sepp->se_next) {
                if (sepp == sep)
                        continue;
		if (sepp->se_checked == 0 ||
                    !sepp->se_rpc ||
		    strcmp(sep->se_proto, sepp->se_proto) != 0 ||
                    sep->se_rpc_prog != sepp->se_rpc_prog)
			continue;
		if (sepp->se_family == AF_INET)
			netid4 = NULL;
		if (sepp->se_family == AF_INET6) {
			netid6 = NULL;
			if (!sep->se_nomapped)
				netid4 = NULL;
		}
		if (netid4 == NULL && netid6 == NULL)
			return;
        }
        if (debug)
                print_service("UNREG", sep);
        for (i = sep->se_rpc_lowvers; i <= sep->se_rpc_highvers; i++) {
		if (netid4)
			rpcb_unset(sep->se_rpc_prog, i, netid4);
		if (netid6)
			rpcb_unset(sep->se_rpc_prog, i, netid6);
	}
        if (sep->se_fd != -1)
                (void) close(sep->se_fd);
        sep->se_fd = -1;
	(void) sigsetmask(omask);
}