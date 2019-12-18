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
struct tty {int t_cflag; int t_state; scalar_t__ t_actout; int /*<<< orphan*/  t_dev; } ;
struct rp_port {int /*<<< orphan*/  rp_channel; } ;
typedef  int /*<<< orphan*/  CHANNEL_t ;

/* Variables and functions */
 int CHANINT_EN ; 
 scalar_t__ FALSE ; 
 int HUPCL ; 
 scalar_t__ ISCALLOUT (int /*<<< orphan*/ ) ; 
 int MCINT_EN ; 
 int RXINT_EN ; 
 int SRCINT_EN ; 
 scalar_t__* TSA_CARR_ON (struct tty*) ; 
 int TS_ISOPEN ; 
 int TXINT_EN ; 
 int /*<<< orphan*/  sClrDTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sClrTxXOFF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sDisCTSFlowCtl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sDisInterrupts (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sDisRTSFlowCtl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sDisTransmit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sDisTxSoftFlowCtl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sFlushRxFIFO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sFlushTxFIFO (int /*<<< orphan*/ *) ; 
 struct rp_port* tty_softc (struct tty*) ; 
 int /*<<< orphan*/  wakeup (scalar_t__*) ; 

__attribute__((used)) static void
rphardclose(struct tty *tp)
{
	struct	rp_port	*rp;
	CHANNEL_t	*cp;

	rp = tty_softc(tp);
	cp = &rp->rp_channel;

	sFlushRxFIFO(cp);
	sFlushTxFIFO(cp);
	sDisTransmit(cp);
	sDisInterrupts(cp, TXINT_EN|MCINT_EN|RXINT_EN|SRCINT_EN|CHANINT_EN);
	sDisRTSFlowCtl(cp);
	sDisCTSFlowCtl(cp);
	sDisTxSoftFlowCtl(cp);
	sClrTxXOFF(cp);

#ifdef DJA
	if(tp->t_cflag&HUPCL || !(tp->t_state&TS_ISOPEN) || !tp->t_actout) {
		sClrDTR(cp);
	}
	if(ISCALLOUT(tp->t_dev)) {
		sClrDTR(cp);
	}
	tp->t_actout = FALSE;
	wakeup(&tp->t_actout);
	wakeup(TSA_CARR_ON(tp));
#endif /* DJA */
}