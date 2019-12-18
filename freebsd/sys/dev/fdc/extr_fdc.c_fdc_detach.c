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
struct fdc_data {int flags; int /*<<< orphan*/  fdc_mtx; int /*<<< orphan*/  dmachan; int /*<<< orphan*/  fdc_thread; int /*<<< orphan*/  head; int /*<<< orphan*/ * fdc_intr; int /*<<< orphan*/  res_irq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int FDC_KTHREAD_ALIVE ; 
 int FDC_KTHREAD_EXIT ; 
 int FDC_NODMA ; 
 int /*<<< orphan*/  PRIBIO ; 
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct fdc_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdc_release_resources (struct fdc_data*) ; 
 int /*<<< orphan*/  fdout_wr (struct fdc_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isa_dma_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

int
fdc_detach(device_t dev)
{
	struct	fdc_data *fdc;
	int	error;

	fdc = device_get_softc(dev);

	/* have our children detached first */
	if ((error = bus_generic_detach(dev)))
		return (error);

	if (fdc->fdc_intr)
		bus_teardown_intr(dev, fdc->res_irq, fdc->fdc_intr);
	fdc->fdc_intr = NULL;

	/* kill worker thread */
	mtx_lock(&fdc->fdc_mtx);
	fdc->flags |= FDC_KTHREAD_EXIT;
	wakeup(&fdc->head);
	while ((fdc->flags & FDC_KTHREAD_ALIVE) != 0)
		msleep(fdc->fdc_thread, &fdc->fdc_mtx, PRIBIO, "fdcdet", 0);
	mtx_unlock(&fdc->fdc_mtx);

	/* reset controller, turn motor off */
	fdout_wr(fdc, 0);

	if (!(fdc->flags & FDC_NODMA))
		isa_dma_release(fdc->dmachan);
	fdc_release_resources(fdc);
	mtx_destroy(&fdc->fdc_mtx);
	return (0);
}