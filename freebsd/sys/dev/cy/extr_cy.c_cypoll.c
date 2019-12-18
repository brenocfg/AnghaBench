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
struct tty {int /*<<< orphan*/  t_state; } ;
struct com_s {int iptr; int ibuf; int state; int last_modem_status; int prev_modem_status; int extra_state; scalar_t__ etc; struct tty* tp; } ;

/* Variables and functions */
 int CD1400_MSVR2_CD ; 
 int /*<<< orphan*/  COM_LOCK () ; 
 int /*<<< orphan*/  COM_UNLOCK () ; 
 int CSE_ODONE ; 
 int CS_BUSY ; 
 int CS_CHECKMSR ; 
 int CS_ODONE ; 
 scalar_t__ ETC_BREAK_ENDED ; 
 scalar_t__ ETC_NONE ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 scalar_t__ LOTS_OF_EVENTS ; 
 int NPORTS ; 
 int /*<<< orphan*/  TS_BUSY ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 struct com_s* cy_addr (int) ; 
 scalar_t__ cy_events ; 
 int /*<<< orphan*/  cy_timeouts ; 
 int /*<<< orphan*/  cyinput (struct com_s*) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  ttwwakeup (struct tty*) ; 
 int /*<<< orphan*/  ttyld_modem (struct tty*,int) ; 
 int /*<<< orphan*/  ttyld_start (struct tty*) ; 
 int /*<<< orphan*/  wakeup (scalar_t__*) ; 

__attribute__((used)) static void
cypoll(void *arg)
{
	int		unit;

#ifdef CyDebug
	++cy_timeouts;
#endif
	if (cy_events == 0)
		return;
repeat:
	for (unit = 0; unit < NPORTS; ++unit) {
		struct com_s	*com;
		int		incc;
		struct tty	*tp;

		com = cy_addr(unit);
		if (com == NULL)
			continue;
		tp = com->tp;
		if (tp == NULL) {
			/*
			 * XXX forget any events related to closed devices
			 * (actually never opened devices) so that we don't
			 * loop.
			 */
			critical_enter();
			COM_LOCK();
			incc = com->iptr - com->ibuf;
			com->iptr = com->ibuf;
			if (com->state & CS_CHECKMSR) {
				incc += LOTS_OF_EVENTS;
				com->state &= ~CS_CHECKMSR;
			}
			cy_events -= incc;
			COM_UNLOCK();
			critical_exit();
			if (incc != 0)
				log(LOG_DEBUG,
				    "cy%d: %d events for device with no tp\n",
				    unit, incc);
			continue;
		}
		if (com->iptr != com->ibuf) {
			critical_enter();
			COM_LOCK();
			cyinput(com);
			COM_UNLOCK();
			critical_exit();
		}
		if (com->state & CS_CHECKMSR) {
			u_char	delta_modem_status;

			critical_enter();
			COM_LOCK();
			cyinput(com);
			delta_modem_status = com->last_modem_status
					     ^ com->prev_modem_status;
			com->prev_modem_status = com->last_modem_status;
			cy_events -= LOTS_OF_EVENTS;
			com->state &= ~CS_CHECKMSR;
			COM_UNLOCK();
			critical_exit();
			if (delta_modem_status & CD1400_MSVR2_CD)
				ttyld_modem(tp,
				    com->prev_modem_status & CD1400_MSVR2_CD);
		}
		if (com->extra_state & CSE_ODONE) {
			critical_enter();
			COM_LOCK();
			cy_events -= LOTS_OF_EVENTS;
			com->extra_state &= ~CSE_ODONE;
			COM_UNLOCK();
			critical_exit();
			if (!(com->state & CS_BUSY)) {
				tp->t_state &= ~TS_BUSY;
				ttwwakeup(com->tp);
			}
			if (com->etc != ETC_NONE) {
				if (com->etc == ETC_BREAK_ENDED)
					com->etc = ETC_NONE;
				wakeup(&com->etc);
			}
		}
		if (com->state & CS_ODONE) {
			critical_enter();
			COM_LOCK();
			cy_events -= LOTS_OF_EVENTS;
			com->state &= ~CS_ODONE;
			COM_UNLOCK();
			critical_exit();
			ttyld_start(tp);
		}
		if (cy_events == 0)
			break;
	}
	if (cy_events >= LOTS_OF_EVENTS)
		goto repeat;
}