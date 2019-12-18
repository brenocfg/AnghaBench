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
typedef  int u_char ;
struct seq_softc {int unit; int timerbase; int tempo; int /*<<< orphan*/  music; int /*<<< orphan*/  reset_cv; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEQ_DEBUG (int,int /*<<< orphan*/ ) ; 
 int SEQ_ECHO ; 
#define  TMR_CONTINUE 135 
#define  TMR_ECHO 134 
#define  TMR_START 133 
#define  TMR_STOP 132 
#define  TMR_TEMPO 131 
#define  TMR_TIMERBASE 130 
#define  TMR_WAIT_ABS 129 
#define  TMR_WAIT_REL 128 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int /*<<< orphan*/  seq_copytoinput (struct seq_softc*,int*,int) ; 
 int /*<<< orphan*/  timer_continue (struct seq_softc*) ; 
 int /*<<< orphan*/  timer_setvals (struct seq_softc*,int,int) ; 
 int /*<<< orphan*/  timer_start (struct seq_softc*) ; 
 int /*<<< orphan*/  timer_stop (struct seq_softc*) ; 
 int /*<<< orphan*/  timer_wait (struct seq_softc*,int,int) ; 

__attribute__((used)) static int
seq_timing(struct seq_softc *scp, u_char *event)
{
	int param;
	int ret;

	ret = 0;
	param = event[4] + (event[5] << 8) +
	    (event[6] << 16) + (event[7] << 24);

	SEQ_DEBUG(5, printf("seq_timing: unit %d, cmd %d, param %d.\n",
	    scp->unit, event[1], param));
	switch (event[1]) {
	case TMR_WAIT_REL:
		timer_wait(scp, param, 0);
		break;
	case TMR_WAIT_ABS:
		timer_wait(scp, param, 1);
		break;
	case TMR_START:
		timer_start(scp);
		cv_broadcast(&scp->reset_cv);
		break;
	case TMR_STOP:
		timer_stop(scp);
		/*
		 * The following cv_broadcast isn't needed since we only
		 * wait for 0->1 transitions.  It probably won't hurt
		 */
		cv_broadcast(&scp->reset_cv);
		break;
	case TMR_CONTINUE:
		timer_continue(scp);
		cv_broadcast(&scp->reset_cv);
		break;
	case TMR_TEMPO:
		if (param < 8)
			param = 8;
		if (param > 360)
			param = 360;
		SEQ_DEBUG(4, printf("Timer set tempo %d\n", param));
		timer_setvals(scp, param, scp->timerbase);
		break;
	case TMR_TIMERBASE:
		if (param < 1)
			param = 1;
		if (param > 1000)
			param = 1000;
		SEQ_DEBUG(4, printf("Timer set timerbase %d\n", param));
		timer_setvals(scp, scp->tempo, param);
		break;
	case TMR_ECHO:
		/*
		 * TODO: Consider making 4-byte events for /dev/sequencer
		 * PRO: Maybe needed by legacy apps
		 * CON: soundcard.h has been warning for a while many years
		 * to expect 8 byte events.
		 */
#if 0
		if (scp->music)
			seq_copytoinput(scp, event, 8);
		else {
			param = (param << 8 | SEQ_ECHO);
			seq_copytoinput(scp, (u_char *)&param, 4);
		}
#else
		seq_copytoinput(scp, event, 8);
#endif
		break;
	default:
		SEQ_DEBUG(2, printf("seq_timing event type %d not handled.\n",
		    event[1]));
		ret = 1;
		break;
	}
	return ret;
}