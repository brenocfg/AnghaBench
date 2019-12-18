#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct tty {int dummy; } ;
struct TYPE_16__ {int* TxControl; } ;
struct rp_port {unsigned int rp_intmask; TYPE_1__* rp_ctlp; int /*<<< orphan*/  rp_timer; TYPE_2__ rp_channel; } ;
struct TYPE_15__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CHANINT_EN ; 
 int MCINT_EN ; 
 int /*<<< orphan*/  POLL_INTERVAL ; 
 int RXINT_EN ; 
 int SET_DTR ; 
 int SET_RTS ; 
 int SRCINT_EN ; 
 int /*<<< orphan*/  TRIG_1 ; 
 int TXINT_EN ; 
 int /*<<< orphan*/  _INDX_ADDR ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rp_port*) ; 
 int /*<<< orphan*/  device_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32dec (int*) ; 
 int /*<<< orphan*/  rp_do_poll ; 
 int /*<<< orphan*/  rp_writech4 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sClrTxXOFF (TYPE_2__*) ; 
 int /*<<< orphan*/  sDisRxStatusMode (TYPE_2__*) ; 
 int /*<<< orphan*/  sDisTxSoftFlowCtl (TYPE_2__*) ; 
 int /*<<< orphan*/  sEnInterrupts (TYPE_2__*,int) ; 
 int /*<<< orphan*/  sEnRxFIFO (TYPE_2__*) ; 
 int /*<<< orphan*/  sEnTransmit (TYPE_2__*) ; 
 int /*<<< orphan*/  sFlushRxFIFO (TYPE_2__*) ; 
 int /*<<< orphan*/  sFlushTxFIFO (TYPE_2__*) ; 
 unsigned int sGetChanIntID (TYPE_2__*) ; 
 unsigned int sGetChanStatus (TYPE_2__*) ; 
 int /*<<< orphan*/  sSetRxTrigger (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sStartRxProcessor (TYPE_2__*) ; 
 struct rp_port* tty_softc (struct tty*) ; 

__attribute__((used)) static int
rpopen(struct tty *tp)
{
	struct	rp_port *rp;
	int	flags;
	unsigned int	IntMask, ChanStatus;

	rp = tty_softc(tp);

	flags = 0;
	flags |= SET_RTS;
	flags |= SET_DTR;
	rp->rp_channel.TxControl[3] =
		((rp->rp_channel.TxControl[3]
		& ~(SET_RTS | SET_DTR)) | flags);
	rp_writech4(&rp->rp_channel,_INDX_ADDR,
		le32dec(rp->rp_channel.TxControl));
	sSetRxTrigger(&rp->rp_channel, TRIG_1);
	sDisRxStatusMode(&rp->rp_channel);
	sFlushRxFIFO(&rp->rp_channel);
	sFlushTxFIFO(&rp->rp_channel);

	sEnInterrupts(&rp->rp_channel,
		(TXINT_EN|MCINT_EN|RXINT_EN|SRCINT_EN|CHANINT_EN));
	sSetRxTrigger(&rp->rp_channel, TRIG_1);

	sDisRxStatusMode(&rp->rp_channel);
	sClrTxXOFF(&rp->rp_channel);

/*	sDisRTSFlowCtl(&rp->rp_channel);
	sDisCTSFlowCtl(&rp->rp_channel);
*/
	sDisTxSoftFlowCtl(&rp->rp_channel);

	sStartRxProcessor(&rp->rp_channel);

	sEnRxFIFO(&rp->rp_channel);
	sEnTransmit(&rp->rp_channel);

/*	sSetDTR(&rp->rp_channel);
	sSetRTS(&rp->rp_channel);
*/

	IntMask = sGetChanIntID(&rp->rp_channel);
	IntMask = IntMask & rp->rp_intmask;
	ChanStatus = sGetChanStatus(&rp->rp_channel);

	callout_reset(&rp->rp_timer, POLL_INTERVAL, rp_do_poll, rp);

	device_busy(rp->rp_ctlp->dev);
	return(0);
}