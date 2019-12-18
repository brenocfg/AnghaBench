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
struct TYPE_2__ {int c_cflag; } ;
struct tty {int t_cflag; int t_state; scalar_t__ t_actout; TYPE_1__ t_init_in; struct com_s* t_sc; } ;
struct com_s {int unit; int intr_enable; int prev_modem_status; int channel_control; struct tty* tp; int /*<<< orphan*/ * cor; int /*<<< orphan*/  etc; int /*<<< orphan*/  iobase; } ;
typedef  int /*<<< orphan*/  cy_addr ;

/* Variables and functions */
 int CD1400_CCR_CMDCHANCTL ; 
 int CD1400_CCR_CMDRESET ; 
 int CD1400_CCR_FTF ; 
 int CD1400_CCR_RCVDIS ; 
 int CD1400_CCR_XMTEN ; 
 int /*<<< orphan*/  CD1400_COR2 ; 
 int /*<<< orphan*/  CD1400_COR2_ETC ; 
 int /*<<< orphan*/  CD1400_ETC_STOPBREAK ; 
 int CD1400_MSVR2_CD ; 
 int /*<<< orphan*/  CD1400_SRER ; 
 int CLOCAL ; 
 int /*<<< orphan*/  COM_LOCK () ; 
 int /*<<< orphan*/  COM_UNLOCK () ; 
 int /*<<< orphan*/  ETC_NONE ; 
 scalar_t__ FALSE ; 
 int HUPCL ; 
 int /*<<< orphan*/  SER_DTR ; 
 scalar_t__* TSA_CARR_ON (struct tty*) ; 
 int TS_ISOPEN ; 
 int /*<<< orphan*/  cd1400_channel_cmd (struct com_s*,int) ; 
 int /*<<< orphan*/  cd_etc (struct com_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cd_setreg (struct com_s*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int /*<<< orphan*/  cymodem (struct tty*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int spltty () ; 
 int /*<<< orphan*/  splx (int) ; 
 int /*<<< orphan*/  ttydtrwaitstart (struct tty*) ; 
 int /*<<< orphan*/  wakeup (scalar_t__*) ; 

__attribute__((used)) static void
cyclose(struct tty *tp)
{
	cy_addr		iobase;
	struct com_s	*com;
	int		s;
	int		unit;

	com = tp->t_sc;
	unit = com->unit;
	iobase = com->iobase;
	s = spltty();
	/* XXX */
	critical_enter();
	COM_LOCK();
	com->etc = ETC_NONE;
	cd_setreg(com, CD1400_COR2, com->cor[1] &= ~CD1400_COR2_ETC);
	COM_UNLOCK();
	critical_exit();
	cd_etc(com, CD1400_ETC_STOPBREAK);
	cd1400_channel_cmd(com, CD1400_CCR_CMDRESET | CD1400_CCR_FTF);

	{
		critical_enter();
		COM_LOCK();
		cd_setreg(com, CD1400_SRER, com->intr_enable = 0);
		COM_UNLOCK();
		critical_exit();
		tp = com->tp;
		if ((tp->t_cflag & HUPCL)
		    /*
		     * XXX we will miss any carrier drop between here and the
		     * next open.  Perhaps we should watch DCD even when the
		     * port is closed; it is not sufficient to check it at
		     * the next open because it might go up and down while
		     * we're not watching.
		     */
		    || (!tp->t_actout
		       && !(com->prev_modem_status & CD1400_MSVR2_CD)
		       && !(tp->t_init_in.c_cflag & CLOCAL))
		    || !(tp->t_state & TS_ISOPEN)) {
			(void)cymodem(tp, 0, SER_DTR);

			/* Disable receiver (leave transmitter enabled). */
			com->channel_control = CD1400_CCR_CMDCHANCTL
					       | CD1400_CCR_XMTEN
					       | CD1400_CCR_RCVDIS;
			cd1400_channel_cmd(com, com->channel_control);

			ttydtrwaitstart(tp);
		}
	}
	tp->t_actout = FALSE;
	wakeup(&tp->t_actout);
	wakeup(TSA_CARR_ON(tp));	/* restart any wopeners */
	splx(s);
}