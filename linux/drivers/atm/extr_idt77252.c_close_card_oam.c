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
struct TYPE_4__ {int /*<<< orphan*/  queue; } ;
struct TYPE_3__ {TYPE_2__ rx_pool; } ;
struct vc_map {unsigned long index; TYPE_1__ rcv; } ;
struct idt77252_dev {int vpibits; unsigned long rct_base; int /*<<< orphan*/  name; int /*<<< orphan*/  cmd_lock; struct vc_map** vcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,int /*<<< orphan*/ ) ; 
 unsigned long SAR_CMD_CLOSE_CONNECTION ; 
 int /*<<< orphan*/  SAR_REG_CMD ; 
 unsigned long SAR_SRAM_RCT_SIZE ; 
 int VPCI2VC (struct idt77252_dev*,int,int) ; 
 int /*<<< orphan*/  recycle_rx_pool_skb (struct idt77252_dev*,TYPE_2__*) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  waitfor_idle (struct idt77252_dev*) ; 
 int /*<<< orphan*/  writel (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
close_card_oam(struct idt77252_dev *card)
{
	unsigned long flags;
	unsigned long addr;
	struct vc_map *vc;
	int vpi, vci;
	int index;

	for (vpi = 0; vpi < (1 << card->vpibits); vpi++) {
		for (vci = 3; vci < 5; vci++) {
			index = VPCI2VC(card, vpi, vci);
			vc = card->vcs[index];

			addr = card->rct_base + vc->index * SAR_SRAM_RCT_SIZE;

			spin_lock_irqsave(&card->cmd_lock, flags);
			writel(SAR_CMD_CLOSE_CONNECTION | (addr << 2),
			       SAR_REG_CMD);
			waitfor_idle(card);
			spin_unlock_irqrestore(&card->cmd_lock, flags);

			if (skb_queue_len(&vc->rcv.rx_pool.queue) != 0) {
				DPRINTK("%s: closing a VC "
					"with pending rx buffers.\n",
					card->name);

				recycle_rx_pool_skb(card, &vc->rcv.rx_pool);
			}
		}
	}
}