#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct he_vcc {int rc_index; int /*<<< orphan*/  tx_waitq; int /*<<< orphan*/  rx_waitq; } ;
struct he_tpd {int status; struct atm_vcc* vcc; int /*<<< orphan*/ * skb; } ;
struct he_dev {int /*<<< orphan*/  global_lock; TYPE_4__* cs_stper; int /*<<< orphan*/  total_bw; } ;
struct TYPE_7__ {scalar_t__ traffic_class; } ;
struct TYPE_6__ {scalar_t__ traffic_class; } ;
struct TYPE_8__ {TYPE_2__ txtp; TYPE_1__ rxtp; } ;
struct atm_vcc {int /*<<< orphan*/  flags; TYPE_3__ qos; int /*<<< orphan*/  vci; int /*<<< orphan*/  vpi; int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  sk_wmem_alloc; } ;
struct TYPE_9__ {scalar_t__ inuse; scalar_t__ pcr; } ;

/* Variables and functions */
#define  ATM_CBR 129 
 scalar_t__ ATM_NONE ; 
#define  ATM_UBR 128 
 int /*<<< orphan*/  ATM_VF_ADDR ; 
 int /*<<< orphan*/  ATM_VF_READY ; 
 int /*<<< orphan*/  DECLARE_WAITQUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct he_dev* HE_DEV (int /*<<< orphan*/ ) ; 
 struct he_vcc* HE_VCC (struct atm_vcc*) ; 
 int /*<<< orphan*/  HPRINTK (char*,...) ; 
 int HZ ; 
 int MAX_RETRY ; 
 int RCC_BUSY ; 
 int /*<<< orphan*/  RCC_STAT ; 
 int /*<<< orphan*/  RSR0_CLOSE_CONN ; 
 int /*<<< orphan*/  RXCON_CLOSE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int TPD_EOS ; 
 int TPD_INT ; 
 scalar_t__ TSR0_CONN_STATE (unsigned int volatile) ; 
 int /*<<< orphan*/  TSR14_DELETE ; 
 int TSR1_MCR (int /*<<< orphan*/ ) ; 
 int TSR1_PCR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSR4_FLUSH_CONN ; 
 unsigned int volatile TSR4_SESSION_ENDED ; 
 struct he_tpd* __alloc_tpd (struct he_dev*) ; 
 int /*<<< orphan*/  __enqueue_tpd (struct he_dev*,struct he_tpd*,unsigned int) ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 unsigned int he_mkcid (struct he_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int he_readl (struct he_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  he_readl_rsr0 (struct he_dev*,unsigned int) ; 
 unsigned int he_readl_tsr0 (struct he_dev*,unsigned int) ; 
 unsigned int he_readl_tsr4 (struct he_dev*,unsigned int) ; 
 int /*<<< orphan*/  he_writel_mbox (struct he_dev*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  he_writel_rsr0 (struct he_dev*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  he_writel_tsr1 (struct he_dev*,int,unsigned int) ; 
 int /*<<< orphan*/  he_writel_tsr14_upper (struct he_dev*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  he_writel_tsr4_upper (struct he_dev*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  hprintk (char*,int,...) ; 
 int /*<<< orphan*/  kfree (struct he_vcc*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rate_to_atmf (int) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int schedule_timeout (int) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 TYPE_5__* sk_atm (struct atm_vcc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void
he_close(struct atm_vcc *vcc)
{
	unsigned long flags;
	DECLARE_WAITQUEUE(wait, current);
	struct he_dev *he_dev = HE_DEV(vcc->dev);
	struct he_tpd *tpd;
	unsigned cid;
	struct he_vcc *he_vcc = HE_VCC(vcc);
#define MAX_RETRY 30
	int retry = 0, sleep = 1, tx_inuse;

	HPRINTK("close vcc %p %d.%d\n", vcc, vcc->vpi, vcc->vci);

	clear_bit(ATM_VF_READY, &vcc->flags);
	cid = he_mkcid(he_dev, vcc->vpi, vcc->vci);

	if (vcc->qos.rxtp.traffic_class != ATM_NONE) {
		int timeout;

		HPRINTK("close rx cid 0x%x\n", cid);

		/* 2.7.2.2 close receive operation */

		/* wait for previous close (if any) to finish */

		spin_lock_irqsave(&he_dev->global_lock, flags);
		while (he_readl(he_dev, RCC_STAT) & RCC_BUSY) {
			HPRINTK("close cid 0x%x RCC_BUSY\n", cid);
			udelay(250);
		}

		set_current_state(TASK_UNINTERRUPTIBLE);
		add_wait_queue(&he_vcc->rx_waitq, &wait);

		he_writel_rsr0(he_dev, RSR0_CLOSE_CONN, cid);
		(void) he_readl_rsr0(he_dev, cid);		/* flush posted writes */
		he_writel_mbox(he_dev, cid, RXCON_CLOSE);
		spin_unlock_irqrestore(&he_dev->global_lock, flags);

		timeout = schedule_timeout(30*HZ);

		remove_wait_queue(&he_vcc->rx_waitq, &wait);
		set_current_state(TASK_RUNNING);

		if (timeout == 0)
			hprintk("close rx timeout cid 0x%x\n", cid);

		HPRINTK("close rx cid 0x%x complete\n", cid);

	}

	if (vcc->qos.txtp.traffic_class != ATM_NONE) {
		volatile unsigned tsr4, tsr0;
		int timeout;

		HPRINTK("close tx cid 0x%x\n", cid);
		
		/* 2.1.2
		 *
		 * ... the host must first stop queueing packets to the TPDRQ
		 * on the connection to be closed, then wait for all outstanding
		 * packets to be transmitted and their buffers returned to the
		 * TBRQ. When the last packet on the connection arrives in the
		 * TBRQ, the host issues the close command to the adapter.
		 */

		while (((tx_inuse = refcount_read(&sk_atm(vcc)->sk_wmem_alloc)) > 1) &&
		       (retry < MAX_RETRY)) {
			msleep(sleep);
			if (sleep < 250)
				sleep = sleep * 2;

			++retry;
		}

		if (tx_inuse > 1)
			hprintk("close tx cid 0x%x tx_inuse = %d\n", cid, tx_inuse);

		/* 2.3.1.1 generic close operations with flush */

		spin_lock_irqsave(&he_dev->global_lock, flags);
		he_writel_tsr4_upper(he_dev, TSR4_FLUSH_CONN, cid);
					/* also clears TSR4_SESSION_ENDED */

		switch (vcc->qos.txtp.traffic_class) {
			case ATM_UBR:
				he_writel_tsr1(he_dev, 
					TSR1_MCR(rate_to_atmf(200000))
					| TSR1_PCR(0), cid);
				break;
			case ATM_CBR:
				he_writel_tsr14_upper(he_dev, TSR14_DELETE, cid);
				break;
		}
		(void) he_readl_tsr4(he_dev, cid);		/* flush posted writes */

		tpd = __alloc_tpd(he_dev);
		if (tpd == NULL) {
			hprintk("close tx he_alloc_tpd failed cid 0x%x\n", cid);
			goto close_tx_incomplete;
		}
		tpd->status |= TPD_EOS | TPD_INT;
		tpd->skb = NULL;
		tpd->vcc = vcc;
		wmb();

		set_current_state(TASK_UNINTERRUPTIBLE);
		add_wait_queue(&he_vcc->tx_waitq, &wait);
		__enqueue_tpd(he_dev, tpd, cid);
		spin_unlock_irqrestore(&he_dev->global_lock, flags);

		timeout = schedule_timeout(30*HZ);

		remove_wait_queue(&he_vcc->tx_waitq, &wait);
		set_current_state(TASK_RUNNING);

		spin_lock_irqsave(&he_dev->global_lock, flags);

		if (timeout == 0) {
			hprintk("close tx timeout cid 0x%x\n", cid);
			goto close_tx_incomplete;
		}

		while (!((tsr4 = he_readl_tsr4(he_dev, cid)) & TSR4_SESSION_ENDED)) {
			HPRINTK("close tx cid 0x%x !TSR4_SESSION_ENDED (tsr4 = 0x%x)\n", cid, tsr4);
			udelay(250);
		}

		while (TSR0_CONN_STATE(tsr0 = he_readl_tsr0(he_dev, cid)) != 0) {
			HPRINTK("close tx cid 0x%x TSR0_CONN_STATE != 0 (tsr0 = 0x%x)\n", cid, tsr0);
			udelay(250);
		}

close_tx_incomplete:

		if (vcc->qos.txtp.traffic_class == ATM_CBR) {
			int reg = he_vcc->rc_index;

			HPRINTK("cs_stper reg = %d\n", reg);

			if (he_dev->cs_stper[reg].inuse == 0)
				hprintk("cs_stper[%d].inuse = 0!\n", reg);
			else
				--he_dev->cs_stper[reg].inuse;

			he_dev->total_bw -= he_dev->cs_stper[reg].pcr;
		}
		spin_unlock_irqrestore(&he_dev->global_lock, flags);

		HPRINTK("close tx cid 0x%x complete\n", cid);
	}

	kfree(he_vcc);

	clear_bit(ATM_VF_ADDR, &vcc->flags);
}