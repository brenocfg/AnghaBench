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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/  rx_pool; } ;
struct vc_map {int index; TYPE_1__ rcv; int /*<<< orphan*/  flags; struct atm_vcc* rx_vcc; } ;
struct idt77252_dev {int rct_base; int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/  name; } ;
struct atm_vcc {int vci; } ;
struct TYPE_4__ {scalar_t__ max_sdu; } ;
struct atm_qos {int aal; TYPE_2__ rxtp; } ;

/* Variables and functions */
#define  ATM_AAL0 131 
#define  ATM_AAL1 130 
#define  ATM_AAL34 129 
#define  ATM_AAL5 128 
 int EBUSY ; 
 int /*<<< orphan*/  OPRINTK (char*,int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long SAR_CMD_OPEN_CONNECTION ; 
 scalar_t__ SAR_FB_SIZE_0 ; 
 scalar_t__ SAR_FB_SIZE_1 ; 
 scalar_t__ SAR_FB_SIZE_2 ; 
 int /*<<< orphan*/  SAR_RCTE_AAL34 ; 
 int /*<<< orphan*/  SAR_RCTE_AAL5 ; 
 int /*<<< orphan*/  SAR_RCTE_CONNECTOPEN ; 
 int /*<<< orphan*/  SAR_RCTE_FBP_01 ; 
 int /*<<< orphan*/  SAR_RCTE_FBP_1 ; 
 int /*<<< orphan*/  SAR_RCTE_FBP_2 ; 
 int /*<<< orphan*/  SAR_RCTE_FBP_3 ; 
 int /*<<< orphan*/  SAR_RCTE_OAM ; 
 int /*<<< orphan*/  SAR_RCTE_RAWCELLINTEN ; 
 int /*<<< orphan*/  SAR_RCTE_RCQ ; 
 int /*<<< orphan*/  SAR_REG_CMD ; 
 int /*<<< orphan*/  VCF_RX ; 
 int /*<<< orphan*/  flush_rx_pool (struct idt77252_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waitfor_idle (struct idt77252_dev*) ; 
 int /*<<< orphan*/  write_sram (struct idt77252_dev*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
idt77252_init_rx(struct idt77252_dev *card, struct vc_map *vc,
		 struct atm_vcc *vcc, struct atm_qos *qos)
{
	unsigned long flags;
	unsigned long addr;
	u32 rcte = 0;

	if (test_bit(VCF_RX, &vc->flags))
		return -EBUSY;

	vc->rx_vcc = vcc;
	set_bit(VCF_RX, &vc->flags);

	if ((vcc->vci == 3) || (vcc->vci == 4))
		return 0;

	flush_rx_pool(card, &vc->rcv.rx_pool);

	rcte |= SAR_RCTE_CONNECTOPEN;
	rcte |= SAR_RCTE_RAWCELLINTEN;

	switch (qos->aal) {
		case ATM_AAL0:
			rcte |= SAR_RCTE_RCQ;
			break;
		case ATM_AAL1:
			rcte |= SAR_RCTE_OAM; /* Let SAR drop Video */
			break;
		case ATM_AAL34:
			rcte |= SAR_RCTE_AAL34;
			break;
		case ATM_AAL5:
			rcte |= SAR_RCTE_AAL5;
			break;
		default:
			rcte |= SAR_RCTE_RCQ;
			break;
	}

	if (qos->aal != ATM_AAL5)
		rcte |= SAR_RCTE_FBP_1;
	else if (qos->rxtp.max_sdu > SAR_FB_SIZE_2)
		rcte |= SAR_RCTE_FBP_3;
	else if (qos->rxtp.max_sdu > SAR_FB_SIZE_1)
		rcte |= SAR_RCTE_FBP_2;
	else if (qos->rxtp.max_sdu > SAR_FB_SIZE_0)
		rcte |= SAR_RCTE_FBP_1;
	else
		rcte |= SAR_RCTE_FBP_01;

	addr = card->rct_base + (vc->index << 2);

	OPRINTK("%s: writing RCT at 0x%lx\n", card->name, addr);
	write_sram(card, addr, rcte);

	spin_lock_irqsave(&card->cmd_lock, flags);
	writel(SAR_CMD_OPEN_CONNECTION | (addr << 2), SAR_REG_CMD);
	waitfor_idle(card);
	spin_unlock_irqrestore(&card->cmd_lock, flags);

	return 0;
}