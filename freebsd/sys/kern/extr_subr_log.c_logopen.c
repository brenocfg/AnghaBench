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
struct thread {TYPE_1__* td_proc; } ;
struct cdev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  sc_sigio; int /*<<< orphan*/  sc_callout; } ;
struct TYPE_3__ {int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_PREL (int) ; 
 int EBUSY ; 
 int SBT_1S ; 
 int /*<<< orphan*/  callout_reset_sbt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsetown (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int log_open ; 
 int log_wakeups_per_second ; 
 TYPE_2__ logsoftc ; 
 int /*<<< orphan*/  logtimeout ; 
 int /*<<< orphan*/  msgbuf_lock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static	int
logopen(struct cdev *dev, int flags, int mode, struct thread *td)
{

	if (log_wakeups_per_second < 1) {
		printf("syslog wakeup is less than one.  Adjusting to 1.\n");
		log_wakeups_per_second = 1;
	}

	mtx_lock(&msgbuf_lock);
	if (log_open) {
		mtx_unlock(&msgbuf_lock);
		return (EBUSY);
	}
	log_open = 1;
	callout_reset_sbt(&logsoftc.sc_callout,
	    SBT_1S / log_wakeups_per_second, 0, logtimeout, NULL, C_PREL(1));
	mtx_unlock(&msgbuf_lock);

	fsetown(td->td_proc->p_pid, &logsoftc.sc_sigio);	/* signal process only */
	return (0);
}