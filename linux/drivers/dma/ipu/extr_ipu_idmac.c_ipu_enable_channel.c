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
typedef  unsigned long uint32_t ;
struct ipu {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int chan_id; } ;
struct idmac_channel {int /*<<< orphan*/  status; scalar_t__ active_buffer; TYPE_1__ dma_chan; } ;
struct idmac {int dummy; } ;
typedef  enum ipu_channel { ____Placeholder_ipu_channel } ipu_channel ;

/* Variables and functions */
 int /*<<< orphan*/  IDMAC_CHA_EN ; 
#define  IDMAC_IC_7 130 
#define  IDMAC_SDC_0 129 
#define  IDMAC_SDC_1 128 
 int /*<<< orphan*/  IPU_CHANNEL_ENABLED ; 
 int /*<<< orphan*/  IPU_CHA_CUR_BUF ; 
 unsigned long idmac_read_icreg (struct ipu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idmac_write_icreg (struct ipu*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idmac_write_ipureg (struct ipu*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_channel_set_priority (struct ipu*,int,int) ; 
 int /*<<< orphan*/  ipu_ic_enable_task (struct ipu*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct ipu* to_ipu (struct idmac*) ; 

__attribute__((used)) static int ipu_enable_channel(struct idmac *idmac, struct idmac_channel *ichan)
{
	struct ipu *ipu = to_ipu(idmac);
	enum ipu_channel channel = ichan->dma_chan.chan_id;
	uint32_t reg;
	unsigned long flags;

	spin_lock_irqsave(&ipu->lock, flags);

	/* Reset to buffer 0 */
	idmac_write_ipureg(ipu, 1UL << channel, IPU_CHA_CUR_BUF);
	ichan->active_buffer = 0;
	ichan->status = IPU_CHANNEL_ENABLED;

	switch (channel) {
	case IDMAC_SDC_0:
	case IDMAC_SDC_1:
	case IDMAC_IC_7:
		ipu_channel_set_priority(ipu, channel, true);
	default:
		break;
	}

	reg = idmac_read_icreg(ipu, IDMAC_CHA_EN);

	idmac_write_icreg(ipu, reg | (1UL << channel), IDMAC_CHA_EN);

	ipu_ic_enable_task(ipu, channel);

	spin_unlock_irqrestore(&ipu->lock, flags);
	return 0;
}