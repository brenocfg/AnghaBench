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
struct thread {int /*<<< orphan*/  td_proc; } ;
struct rtprio {int /*<<< orphan*/  type; int /*<<< orphan*/  prio; } ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_SLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_SUNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTP_PRIO_IDLE ; 
 int /*<<< orphan*/  RTP_PRIO_MAX ; 
 int /*<<< orphan*/  SW_VOL ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  ether_poll (int /*<<< orphan*/ ) ; 
 int hz ; 
 int idlepoll_sleeping ; 
 int /*<<< orphan*/  mi_switch (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_each_burst ; 
 scalar_t__ poll_handlers ; 
 scalar_t__ poll_in_idle_loop ; 
 int /*<<< orphan*/  rtp_to_pri (struct rtprio*,struct thread*) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 
 int /*<<< orphan*/  tsleep (int*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
poll_idle(void)
{
	struct thread *td = curthread;
	struct rtprio rtp;

	rtp.prio = RTP_PRIO_MAX;	/* lowest priority */
	rtp.type = RTP_PRIO_IDLE;
	PROC_SLOCK(td->td_proc);
	rtp_to_pri(&rtp, td);
	PROC_SUNLOCK(td->td_proc);

	for (;;) {
		if (poll_in_idle_loop && poll_handlers > 0) {
			idlepoll_sleeping = 0;
			ether_poll(poll_each_burst);
			thread_lock(td);
			mi_switch(SW_VOL, NULL);
			thread_unlock(td);
		} else {
			idlepoll_sleeping = 1;
			tsleep(&idlepoll_sleeping, 0, "pollid", hz * 3);
		}
	}
}