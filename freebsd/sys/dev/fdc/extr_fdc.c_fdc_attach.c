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
struct fdc_data {int flags; int /*<<< orphan*/  head; scalar_t__ fdout; int /*<<< orphan*/  fdc_mtx; int /*<<< orphan*/  fdcu; int /*<<< orphan*/  dmachan; int /*<<< orphan*/  fdc_intr; int /*<<< orphan*/  res_irq; int /*<<< orphan*/  fdc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int FDC_NEEDS_RESET ; 
 int FDC_NODMA ; 
 int FDC_NOFAST ; 
 int INTR_ENTROPY ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_BIO ; 
 int /*<<< orphan*/  MAX_BYTES_PER_CYL ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  bioq_init (int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct fdc_data*,int /*<<< orphan*/ *) ; 
 struct fdc_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int fdc_initial_reset (int /*<<< orphan*/ ,struct fdc_data*) ; 
 int /*<<< orphan*/ * fdc_intr ; 
 int /*<<< orphan*/ * fdc_intr_fast ; 
 int /*<<< orphan*/  fdout_wr (struct fdc_data*,scalar_t__) ; 
 int hz ; 
 int isa_dma_acquire (int /*<<< orphan*/ ) ; 
 int isa_dma_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isa_dma_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int settle ; 

int
fdc_attach(device_t dev)
{
	struct	fdc_data *fdc;
	int	error;

	fdc = device_get_softc(dev);
	fdc->fdc_dev = dev;
	error = fdc_initial_reset(dev, fdc);
	if (error) {
		device_printf(dev, "does not respond\n");
		return (error);
	}
	error = bus_setup_intr(dev, fdc->res_irq,
	    INTR_TYPE_BIO | INTR_ENTROPY | 
	    ((fdc->flags & FDC_NOFAST) ? INTR_MPSAFE : 0),		       
            ((fdc->flags & FDC_NOFAST) ? NULL : fdc_intr_fast), 	    
	    ((fdc->flags & FDC_NOFAST) ? fdc_intr : NULL), 
			       fdc, &fdc->fdc_intr);
	if (error) {
		device_printf(dev, "cannot setup interrupt\n");
		return (error);
	}
	if (!(fdc->flags & FDC_NODMA)) {
		error = isa_dma_acquire(fdc->dmachan);
		if (!error) {
			error = isa_dma_init(fdc->dmachan,
			    MAX_BYTES_PER_CYL, M_WAITOK);
			if (error)
				isa_dma_release(fdc->dmachan);
		}
		if (error)
			return (error);
	}
	fdc->fdcu = device_get_unit(dev);
	fdc->flags |= FDC_NEEDS_RESET;

	mtx_init(&fdc->fdc_mtx, "fdc lock", NULL, MTX_DEF);

	/* reset controller, turn motor off, clear fdout mirror reg */
	fdout_wr(fdc, fdc->fdout = 0);
	bioq_init(&fdc->head);

	settle = hz / 8;

	return (0);
}