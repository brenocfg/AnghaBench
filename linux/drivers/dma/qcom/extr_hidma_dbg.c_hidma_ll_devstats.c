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
struct seq_file {int dummy; } ;
struct hidma_lldev {int /*<<< orphan*/ * tre_write_offset; int /*<<< orphan*/ * evre_processed_off; int /*<<< orphan*/ * evre_ring_size; int /*<<< orphan*/  evre_dma; int /*<<< orphan*/ * evre_ring; int /*<<< orphan*/ * evca; int /*<<< orphan*/  pending_tre_count; int /*<<< orphan*/ * tre_processed_off; int /*<<< orphan*/ * tre_ring_size; int /*<<< orphan*/  tre_dma; int /*<<< orphan*/ * tre_ring; int /*<<< orphan*/ * trca; int /*<<< orphan*/ * nr_tres; int /*<<< orphan*/ * chidx; int /*<<< orphan*/ * evch_state; int /*<<< orphan*/ * trch_state; int /*<<< orphan*/ * initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/ * atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static void hidma_ll_devstats(struct seq_file *s, void *llhndl)
{
	struct hidma_lldev *lldev = llhndl;

	seq_puts(s, "------Device -----\n");
	seq_printf(s, "lldev init = 0x%x\n", lldev->initialized);
	seq_printf(s, "trch_state = 0x%x\n", lldev->trch_state);
	seq_printf(s, "evch_state = 0x%x\n", lldev->evch_state);
	seq_printf(s, "chidx = 0x%x\n", lldev->chidx);
	seq_printf(s, "nr_tres = 0x%x\n", lldev->nr_tres);
	seq_printf(s, "trca=%p\n", lldev->trca);
	seq_printf(s, "tre_ring=%p\n", lldev->tre_ring);
	seq_printf(s, "tre_ring_handle=%pap\n", &lldev->tre_dma);
	seq_printf(s, "tre_ring_size = 0x%x\n", lldev->tre_ring_size);
	seq_printf(s, "tre_processed_off = 0x%x\n", lldev->tre_processed_off);
	seq_printf(s, "pending_tre_count=%d\n",
			atomic_read(&lldev->pending_tre_count));
	seq_printf(s, "evca=%p\n", lldev->evca);
	seq_printf(s, "evre_ring=%p\n", lldev->evre_ring);
	seq_printf(s, "evre_ring_handle=%pap\n", &lldev->evre_dma);
	seq_printf(s, "evre_ring_size = 0x%x\n", lldev->evre_ring_size);
	seq_printf(s, "evre_processed_off = 0x%x\n", lldev->evre_processed_off);
	seq_printf(s, "tre_write_offset = 0x%x\n", lldev->tre_write_offset);
}