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
struct tcpcb {TYPE_1__* t_fb; } ;
struct socket {int dummy; } ;
struct inpcb {int inp_flags; } ;
struct epoch_tracker {int dummy; } ;
struct TYPE_2__ {int (* tfb_tcp_output ) (struct tcpcb*) ;} ;

/* Variables and functions */
 int ECONNRESET ; 
 int INP_DROPPED ; 
 int INP_TIMEWAIT ; 
 int /*<<< orphan*/  INP_WLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  INP_WUNLOCK (struct inpcb*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  NET_EPOCH_ENTER (struct epoch_tracker) ; 
 int /*<<< orphan*/  NET_EPOCH_EXIT (struct epoch_tracker) ; 
 int /*<<< orphan*/  PRU_SHUTDOWN ; 
 int /*<<< orphan*/  TCPDEBUG0 ; 
 int /*<<< orphan*/  TCPDEBUG1 () ; 
 int /*<<< orphan*/  TCPDEBUG2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCP_PROBE2 (int /*<<< orphan*/ ,struct tcpcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug__user ; 
 struct tcpcb* intotcpcb (struct inpcb*) ; 
 int /*<<< orphan*/  socantsendmore (struct socket*) ; 
 struct inpcb* sotoinpcb (struct socket*) ; 
 int stub1 (struct tcpcb*) ; 
 int /*<<< orphan*/  tcp_usrclosed (struct tcpcb*) ; 

__attribute__((used)) static int
tcp_usr_shutdown(struct socket *so)
{
	int error = 0;
	struct inpcb *inp;
	struct tcpcb *tp = NULL;
	struct epoch_tracker et;

	TCPDEBUG0;
	NET_EPOCH_ENTER(et);
	inp = sotoinpcb(so);
	KASSERT(inp != NULL, ("inp == NULL"));
	INP_WLOCK(inp);
	if (inp->inp_flags & (INP_TIMEWAIT | INP_DROPPED)) {
		error = ECONNRESET;
		goto out;
	}
	tp = intotcpcb(inp);
	TCPDEBUG1();
	socantsendmore(so);
	tcp_usrclosed(tp);
	if (!(inp->inp_flags & INP_DROPPED))
		error = tp->t_fb->tfb_tcp_output(tp);

out:
	TCPDEBUG2(PRU_SHUTDOWN);
	TCP_PROBE2(debug__user, tp, PRU_SHUTDOWN);
	INP_WUNLOCK(inp);
	NET_EPOCH_EXIT(et);

	return (error);
}