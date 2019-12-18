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
struct TYPE_3__ {int /*<<< orphan*/  si_note; } ;
struct TYPE_4__ {int sc_state; int /*<<< orphan*/  sc_callout; int /*<<< orphan*/ * sc_sigio; TYPE_1__ sc_selp; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_PREL (int) ; 
 int /*<<< orphan*/  KNOTE_LOCKED (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int LOG_ASYNC ; 
 int /*<<< orphan*/  LOG_RDPRI ; 
 int SBT_1S ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  callout_reset_sbt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,void (*) (void*),int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_broadcastpri (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_open ; 
 int /*<<< orphan*/  log_wakeup ; 
 int log_wakeups_per_second ; 
 TYPE_2__ logsoftc ; 
 scalar_t__ msgbuftrigger ; 
 int /*<<< orphan*/  pgsigio (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  selwakeuppri (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
logtimeout(void *arg)
{

	if (!log_open)
		return;
	if (msgbuftrigger == 0)
		goto done;
	msgbuftrigger = 0;
	selwakeuppri(&logsoftc.sc_selp, LOG_RDPRI);
	KNOTE_LOCKED(&logsoftc.sc_selp.si_note, 0);
	if ((logsoftc.sc_state & LOG_ASYNC) && logsoftc.sc_sigio != NULL)
		pgsigio(&logsoftc.sc_sigio, SIGIO, 0);
	cv_broadcastpri(&log_wakeup, LOG_RDPRI);
done:
	if (log_wakeups_per_second < 1) {
		printf("syslog wakeup is less than one.  Adjusting to 1.\n");
		log_wakeups_per_second = 1;
	}
	callout_reset_sbt(&logsoftc.sc_callout,
	    SBT_1S / log_wakeups_per_second, 0, logtimeout, NULL, C_PREL(1));
}