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
struct tty {struct com_s* t_sc; } ;
struct com_s {int mcr_image; int mcr_dtr; int mcr_rts; } ;

/* Variables and functions */
 int /*<<< orphan*/  CD1400_MSVR1 ; 
 int /*<<< orphan*/  CD1400_MSVR2 ; 
 int CD1400_MSVR2_CD ; 
 int CD1400_MSVR2_CTS ; 
 int CD1400_MSVR2_DSR ; 
 int CD1400_MSVR2_RI ; 
 int /*<<< orphan*/  COM_LOCK () ; 
 int /*<<< orphan*/  COM_UNLOCK () ; 
 int SER_CTS ; 
 int SER_DCD ; 
 int SER_DSR ; 
 int SER_DTR ; 
 int SER_RI ; 
 int SER_RTS ; 
 int cd_getreg (struct com_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cd_setreg (struct com_s*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 

__attribute__((used)) static int
cymodem(struct tty *tp, int sigon, int sigoff)
{
	struct com_s	*com;
	int	mcr;
	int	msr;

	com = tp->t_sc;
	if (sigon == 0 && sigoff == 0) {
		sigon = 0;
		mcr = com->mcr_image;
		if (mcr & com->mcr_dtr)
			sigon |= SER_DTR;
		if (mcr & com->mcr_rts)
			/* XXX wired on for Cyclom-8Ys */
			sigon |= SER_RTS;

		/*
		 * We must read the modem status from the hardware because
		 * we don't generate modem status change interrupts for all
		 * changes, so com->prev_modem_status is not guaranteed to
		 * be up to date.  This is safe, unlike for sio, because
		 * reading the status register doesn't clear pending modem
		 * status change interrupts.
		 */
		msr = cd_getreg(com, CD1400_MSVR2);

		if (msr & CD1400_MSVR2_CTS)
			sigon |= SER_CTS;
		if (msr & CD1400_MSVR2_CD)
			sigon |= SER_DCD;
		if (msr & CD1400_MSVR2_DSR)
			sigon |= SER_DSR;
		if (msr & CD1400_MSVR2_RI)
			/* XXX not connected except for Cyclom-16Y? */
			sigon |= SER_RI;
		return (sigon);
	}
	mcr = com->mcr_image;
	if (sigon & SER_DTR)
		mcr |= com->mcr_dtr;
	if (sigoff & SER_DTR)
		mcr &= ~com->mcr_dtr;
	if (sigon & SER_RTS)
		mcr |= com->mcr_rts;
	if (sigoff & SER_RTS)
		mcr &= ~com->mcr_rts;
	critical_enter();
	COM_LOCK();
	com->mcr_image = mcr;
	cd_setreg(com, CD1400_MSVR1, mcr);
	cd_setreg(com, CD1400_MSVR2, mcr);
	COM_UNLOCK();
	critical_exit();
	return (0);
}