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
struct seq_file {struct rsxx_cardinfo* private; } ;
struct rsxx_cardinfo {int n_targets; TYPE_2__* ctrl; } ;
struct TYPE_3__ {int /*<<< orphan*/  hw_q_depth; int /*<<< orphan*/  sw_q_depth; int /*<<< orphan*/  dma_cancelled; int /*<<< orphan*/  dma_hw_fault; int /*<<< orphan*/  dma_sw_err; int /*<<< orphan*/  discards_failed; int /*<<< orphan*/  discards_issued; int /*<<< orphan*/  reads_retried; int /*<<< orphan*/  reads_failed; int /*<<< orphan*/  reads_issued; int /*<<< orphan*/  writes_failed; int /*<<< orphan*/  writes_issued; int /*<<< orphan*/  soft_errors; int /*<<< orphan*/  hard_errors; int /*<<< orphan*/  crc_errors; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rsxx_attr_stats_show(struct seq_file *m, void *p)
{
	struct rsxx_cardinfo *card = m->private;
	int i;

	for (i = 0; i < card->n_targets; i++) {
		seq_printf(m, "Ctrl %d CRC Errors	= %d\n",
				i, card->ctrl[i].stats.crc_errors);
		seq_printf(m, "Ctrl %d Hard Errors	= %d\n",
				i, card->ctrl[i].stats.hard_errors);
		seq_printf(m, "Ctrl %d Soft Errors	= %d\n",
				i, card->ctrl[i].stats.soft_errors);
		seq_printf(m, "Ctrl %d Writes Issued	= %d\n",
				i, card->ctrl[i].stats.writes_issued);
		seq_printf(m, "Ctrl %d Writes Failed	= %d\n",
				i, card->ctrl[i].stats.writes_failed);
		seq_printf(m, "Ctrl %d Reads Issued	= %d\n",
				i, card->ctrl[i].stats.reads_issued);
		seq_printf(m, "Ctrl %d Reads Failed	= %d\n",
				i, card->ctrl[i].stats.reads_failed);
		seq_printf(m, "Ctrl %d Reads Retried	= %d\n",
				i, card->ctrl[i].stats.reads_retried);
		seq_printf(m, "Ctrl %d Discards Issued	= %d\n",
				i, card->ctrl[i].stats.discards_issued);
		seq_printf(m, "Ctrl %d Discards Failed	= %d\n",
				i, card->ctrl[i].stats.discards_failed);
		seq_printf(m, "Ctrl %d DMA SW Errors	= %d\n",
				i, card->ctrl[i].stats.dma_sw_err);
		seq_printf(m, "Ctrl %d DMA HW Faults	= %d\n",
				i, card->ctrl[i].stats.dma_hw_fault);
		seq_printf(m, "Ctrl %d DMAs Cancelled	= %d\n",
				i, card->ctrl[i].stats.dma_cancelled);
		seq_printf(m, "Ctrl %d SW Queue Depth	= %d\n",
				i, card->ctrl[i].stats.sw_q_depth);
		seq_printf(m, "Ctrl %d HW Queue Depth	= %d\n",
			i, atomic_read(&card->ctrl[i].stats.hw_q_depth));
	}

	return 0;
}