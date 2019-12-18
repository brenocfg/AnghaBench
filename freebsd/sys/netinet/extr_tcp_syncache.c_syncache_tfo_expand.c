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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  server; } ;
struct tcpcb {unsigned int* t_tfo_pending; int /*<<< orphan*/  iss; int /*<<< orphan*/  snd_nxt; int /*<<< orphan*/  snd_max; TYPE_1__ t_tfo_cookie; int /*<<< orphan*/  t_flags; } ;
struct syncache {int dummy; } ;
struct socket {int dummy; } ;
struct mbuf {int dummy; } ;
struct inpcb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NET_EPOCH_ASSERT () ; 
 int /*<<< orphan*/  TCPSTAT_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TF_FASTOPEN ; 
 int /*<<< orphan*/  atomic_subtract_int (unsigned int*,int) ; 
 struct tcpcb* intotcpcb (struct inpcb*) ; 
 int /*<<< orphan*/  soisconnected (struct socket*) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 
 struct socket* syncache_socket (struct syncache*,struct socket*,struct mbuf*) ; 
 int /*<<< orphan*/  tcps_sc_aborted ; 
 int /*<<< orphan*/  tcps_sc_completed ; 

__attribute__((used)) static void
syncache_tfo_expand(struct syncache *sc, struct socket **lsop, struct mbuf *m,
    uint64_t response_cookie)
{
	struct inpcb *inp;
	struct tcpcb *tp;
	unsigned int *pending_counter;

	NET_EPOCH_ASSERT();

	pending_counter = intotcpcb(sotoinpcb(*lsop))->t_tfo_pending;
	*lsop = syncache_socket(sc, *lsop, m);
	if (*lsop == NULL) {
		TCPSTAT_INC(tcps_sc_aborted);
		atomic_subtract_int(pending_counter, 1);
	} else {
		soisconnected(*lsop);
		inp = sotoinpcb(*lsop);
		tp = intotcpcb(inp);
		tp->t_flags |= TF_FASTOPEN;
		tp->t_tfo_cookie.server = response_cookie;
		tp->snd_max = tp->iss;
		tp->snd_nxt = tp->iss;
		tp->t_tfo_pending = pending_counter;
		TCPSTAT_INC(tcps_sc_completed);
	}
}