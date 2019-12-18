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
struct tty {int dummy; } ;
struct rp_port {int /*<<< orphan*/  rp_overflows; } ;
typedef  int /*<<< orphan*/  CHANNEL_t ;

/* Variables and functions */
 unsigned int RXBREAK ; 
 unsigned int RXFOVERFL ; 
 unsigned int RXFRAME ; 
 unsigned int RXPARITY ; 
 unsigned int STATMODE ; 
 unsigned int STMBREAK ; 
 unsigned int STMFRAMEH ; 
 unsigned int STMPARITYH ; 
 unsigned int STMRCVROVRH ; 
 int TRE_FRAMING ; 
 int TRE_OVERRUN ; 
 int TRE_PARITY ; 
 int rp_readch1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int rp_readch2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sDisRxStatusMode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sEnRxStatusMode (int /*<<< orphan*/ *) ; 
 int sGetRxCnt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sGetTxRxDataIO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int /*<<< orphan*/  ttydisc_rint (struct tty*,int,int) ; 
 int /*<<< orphan*/  ttydisc_rint_done (struct tty*) ; 

__attribute__((used)) static void rp_do_receive(struct rp_port *rp, struct tty *tp,
			CHANNEL_t *cp, unsigned int ChanStatus)
{
	unsigned	int	CharNStat;
	int	ToRecv, ch, err = 0;

	ToRecv = sGetRxCnt(cp);
	if(ToRecv == 0)
		return;

/*	If status indicates there are errored characters in the
	FIFO, then enter status mode (a word in FIFO holds
	characters and status)
*/

	if(ChanStatus & (RXFOVERFL | RXBREAK | RXFRAME | RXPARITY)) {
		if(!(ChanStatus & STATMODE)) {
			ChanStatus |= STATMODE;
			sEnRxStatusMode(cp);
		}
	}
/*
	if we previously entered status mode then read down the
	FIFO one word at a time, pulling apart the character and
	the status. Update error counters depending on status.
*/
	tty_lock(tp);
	if(ChanStatus & STATMODE) {
		while(ToRecv) {
			CharNStat = rp_readch2(cp,sGetTxRxDataIO(cp));
			ch = CharNStat & 0xff;

			if((CharNStat & STMBREAK) || (CharNStat & STMFRAMEH))
				err |= TRE_FRAMING;
			else if (CharNStat & STMPARITYH)
				err |= TRE_PARITY;
			else if (CharNStat & STMRCVROVRH) {
				rp->rp_overflows++;
				err |= TRE_OVERRUN;
			}

			ttydisc_rint(tp, ch, err);
			ToRecv--;
		}
/*
	After emtying FIFO in status mode, turn off status mode
*/

		if(sGetRxCnt(cp) == 0) {
			sDisRxStatusMode(cp);
		}
	} else {
		ToRecv = sGetRxCnt(cp);
		while (ToRecv) {
			ch = rp_readch1(cp,sGetTxRxDataIO(cp));
			ttydisc_rint(tp, ch & 0xff, err);
			ToRecv--;
		}
	}
        ttydisc_rint_done(tp);
        tty_unlock(tp);
}