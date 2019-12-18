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
struct TYPE_2__ {int address; } ;

/* Variables and functions */
 TYPE_1__* FDCS ; 
 int N_FDC ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int buffer_max ; 
 int buffer_min ; 
 scalar_t__ delayed_work_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fd_disable_dma () ; 
 int /*<<< orphan*/  fd_dma_mem_free (unsigned long,long) ; 
 int /*<<< orphan*/  fd_free_dma () ; 
 int /*<<< orphan*/  fd_free_irq () ; 
 int /*<<< orphan*/  fd_timeout ; 
 int /*<<< orphan*/  fd_timer ; 
 int fdc ; 
 int /*<<< orphan*/  floppy_release_regions (int) ; 
 int /*<<< orphan*/ * floppy_track_buffer ; 
 int /*<<< orphan*/  floppy_work ; 
 scalar_t__ irqdma_allocated ; 
 int max_buffer_sectors ; 
 scalar_t__ motor_off_timer ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  set_dor (int,int,int) ; 
 int /*<<< orphan*/  timeout_message ; 
 scalar_t__ timer_pending (scalar_t__) ; 
 int /*<<< orphan*/  usage_count ; 
 scalar_t__ work_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void floppy_release_irq_and_dma(void)
{
	int old_fdc;
#ifndef __sparc__
	int drive;
#endif
	long tmpsize;
	unsigned long tmpaddr;

	if (!atomic_dec_and_test(&usage_count))
		return;

	if (irqdma_allocated) {
		fd_disable_dma();
		fd_free_dma();
		fd_free_irq();
		irqdma_allocated = 0;
	}
	set_dor(0, ~0, 8);
#if N_FDC > 1
	set_dor(1, ~8, 0);
#endif

	if (floppy_track_buffer && max_buffer_sectors) {
		tmpsize = max_buffer_sectors * 1024;
		tmpaddr = (unsigned long)floppy_track_buffer;
		floppy_track_buffer = NULL;
		max_buffer_sectors = 0;
		buffer_min = buffer_max = -1;
		fd_dma_mem_free(tmpaddr, tmpsize);
	}
#ifndef __sparc__
	for (drive = 0; drive < N_FDC * 4; drive++)
		if (timer_pending(motor_off_timer + drive))
			pr_info("motor off timer %d still active\n", drive);
#endif

	if (delayed_work_pending(&fd_timeout))
		pr_info("floppy timer still active:%s\n", timeout_message);
	if (delayed_work_pending(&fd_timer))
		pr_info("auxiliary floppy timer still active\n");
	if (work_pending(&floppy_work))
		pr_info("work still pending\n");
	old_fdc = fdc;
	for (fdc = 0; fdc < N_FDC; fdc++)
		if (FDCS->address != -1)
			floppy_release_regions(fdc);
	fdc = old_fdc;
}