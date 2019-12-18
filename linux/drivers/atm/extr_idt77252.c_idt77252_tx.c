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
typedef  int u32 ;
struct vc_map {int /*<<< orphan*/  flags; int /*<<< orphan*/  index; } ;
struct tsq_entry {int /*<<< orphan*/  word_2; int /*<<< orphan*/  word_1; } ;
struct TYPE_2__ {struct tsq_entry* next; struct tsq_entry* base; struct tsq_entry* last; } ;
struct idt77252_dev {int vpibits; int vcibits; TYPE_1__ tsq; int /*<<< orphan*/  index; int /*<<< orphan*/  name; struct vc_map** vcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAR_REG_TSQB ; 
 int /*<<< orphan*/  SAR_REG_TSQH ; 
 int /*<<< orphan*/  SAR_REG_TSQT ; 
 int SAR_TBD_VCI_SHIFT ; 
 int SAR_TBD_VPI_SHIFT ; 
 int SAR_TSQE_INVALID ; 
 int SAR_TSQE_TAG (int) ; 
 int SAR_TSQE_TYPE ; 
#define  SAR_TSQE_TYPE_IDLE 131 
#define  SAR_TSQE_TYPE_TBD_COMP 130 
#define  SAR_TSQE_TYPE_TIMER 129 
#define  SAR_TSQE_TYPE_TSR 128 
 int /*<<< orphan*/  TXPRINTK (char*,struct tsq_entry*,...) ; 
 int /*<<< orphan*/  VCF_IDLE ; 
 size_t VPCI2VC (struct idt77252_dev*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  XPRINTK (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tsq_entry*) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  drain_scq (struct idt77252_dev*,struct vc_map*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,unsigned int,...) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
idt77252_tx(struct idt77252_dev *card)
{
	struct tsq_entry *tsqe;
	unsigned int vpi, vci;
	struct vc_map *vc;
	u32 conn, stat;

	if (card->tsq.next == card->tsq.last)
		tsqe = card->tsq.base;
	else
		tsqe = card->tsq.next + 1;

	TXPRINTK("idt77252_tx: tsq  %p: base %p, next %p, last %p\n", tsqe,
		 card->tsq.base, card->tsq.next, card->tsq.last);
	TXPRINTK("idt77252_tx: tsqb %08x, tsqt %08x, tsqh %08x, \n",
		 readl(SAR_REG_TSQB),
		 readl(SAR_REG_TSQT),
		 readl(SAR_REG_TSQH));

	stat = le32_to_cpu(tsqe->word_2);

	if (stat & SAR_TSQE_INVALID)
		return;

	do {
		TXPRINTK("tsqe: 0x%p [0x%08x 0x%08x]\n", tsqe,
			 le32_to_cpu(tsqe->word_1),
			 le32_to_cpu(tsqe->word_2));

		switch (stat & SAR_TSQE_TYPE) {
		case SAR_TSQE_TYPE_TIMER:
			TXPRINTK("%s: Timer RollOver detected.\n", card->name);
			break;

		case SAR_TSQE_TYPE_IDLE:

			conn = le32_to_cpu(tsqe->word_1);

			if (SAR_TSQE_TAG(stat) == 0x10) {
#ifdef	NOTDEF
				printk("%s: Connection %d halted.\n",
				       card->name,
				       le32_to_cpu(tsqe->word_1) & 0x1fff);
#endif
				break;
			}

			vc = card->vcs[conn & 0x1fff];
			if (!vc) {
				printk("%s: could not find VC from conn %d\n",
				       card->name, conn & 0x1fff);
				break;
			}

			printk("%s: Connection %d IDLE.\n",
			       card->name, vc->index);

			set_bit(VCF_IDLE, &vc->flags);
			break;

		case SAR_TSQE_TYPE_TSR:

			conn = le32_to_cpu(tsqe->word_1);

			vc = card->vcs[conn & 0x1fff];
			if (!vc) {
				printk("%s: no VC at index %d\n",
				       card->name,
				       le32_to_cpu(tsqe->word_1) & 0x1fff);
				break;
			}

			drain_scq(card, vc);
			break;

		case SAR_TSQE_TYPE_TBD_COMP:

			conn = le32_to_cpu(tsqe->word_1);

			vpi = (conn >> SAR_TBD_VPI_SHIFT) & 0x00ff;
			vci = (conn >> SAR_TBD_VCI_SHIFT) & 0xffff;

			if (vpi >= (1 << card->vpibits) ||
			    vci >= (1 << card->vcibits)) {
				printk("%s: TBD complete: "
				       "out of range VPI.VCI %u.%u\n",
				       card->name, vpi, vci);
				break;
			}

			vc = card->vcs[VPCI2VC(card, vpi, vci)];
			if (!vc) {
				printk("%s: TBD complete: "
				       "no VC at VPI.VCI %u.%u\n",
				       card->name, vpi, vci);
				break;
			}

			drain_scq(card, vc);
			break;
		}

		tsqe->word_2 = cpu_to_le32(SAR_TSQE_INVALID);

		card->tsq.next = tsqe;
		if (card->tsq.next == card->tsq.last)
			tsqe = card->tsq.base;
		else
			tsqe = card->tsq.next + 1;

		TXPRINTK("tsqe: %p: base %p, next %p, last %p\n", tsqe,
			 card->tsq.base, card->tsq.next, card->tsq.last);

		stat = le32_to_cpu(tsqe->word_2);

	} while (!(stat & SAR_TSQE_INVALID));

	writel((unsigned long)card->tsq.next - (unsigned long)card->tsq.base,
	       SAR_REG_TSQH);

	XPRINTK("idt77252_tx-after writel%d: TSQ head = 0x%x, tail = 0x%x, next = 0x%p.\n",
		card->index, readl(SAR_REG_TSQH),
		readl(SAR_REG_TSQT), card->tsq.next);
}