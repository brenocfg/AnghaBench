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
struct fdc_data {int flags; int retry; int /*<<< orphan*/  fdc_mtx; int /*<<< orphan*/ * bp; } ;

/* Variables and functions */
 int FDC_KTHREAD_ALIVE ; 
 int FDC_KTHREAD_EXIT ; 
 int debugflags ; 
 int fdc_worker (struct fdc_data*) ; 
 int /*<<< orphan*/  g_print_bio (char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kproc_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int retry_line ; 

__attribute__((used)) static void
fdc_thread(void *arg)
{
	struct fdc_data *fdc;

	fdc = arg;
	int i;

	mtx_lock(&fdc->fdc_mtx);
	fdc->flags |= FDC_KTHREAD_ALIVE;
	while ((fdc->flags & FDC_KTHREAD_EXIT) == 0) {
		mtx_unlock(&fdc->fdc_mtx);
		i = fdc_worker(fdc);
		if (i && debugflags & 0x20) {
			if (fdc->bp != NULL)
				g_print_bio("", fdc->bp, "");
			printf("Retry line %d\n", retry_line);
		}
		fdc->retry += i;
		mtx_lock(&fdc->fdc_mtx);
	}
	fdc->flags &= ~(FDC_KTHREAD_EXIT | FDC_KTHREAD_ALIVE);
	mtx_unlock(&fdc->fdc_mtx);

	kproc_exit(0);
}