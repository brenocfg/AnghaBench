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
struct fdc_data {scalar_t__ fdct; int fdout; int /*<<< orphan*/  fdc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 scalar_t__ FDC_ENHANCED ; 
 int FDO_FDMAEN ; 
 int FDO_FRST ; 
 int /*<<< orphan*/  I8207X_CONFIG ; 
 int /*<<< orphan*/  I8207X_DSR_SR ; 
 int /*<<< orphan*/  I8207X_DUMPREG ; 
 int /*<<< orphan*/  NE7CMD_SPECIFY ; 
 int debugflags ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ fdc_cmd (struct fdc_data*,int,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  fddsr_wr (struct fdc_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdout_wr (struct fdc_data*,int) ; 
 int fifo_threshold ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  spec1 ; 
 int /*<<< orphan*/  spec2 ; 

__attribute__((used)) static void
fdc_reset(struct fdc_data *fdc)
{
	int i, r[10];

	if (fdc->fdct == FDC_ENHANCED) {
		/* Try a software reset, default precomp, and 500 kb/s */
		fddsr_wr(fdc, I8207X_DSR_SR);
	} else {
		/* Try a hardware reset, keep motor on */
		fdout_wr(fdc, fdc->fdout & ~(FDO_FRST|FDO_FDMAEN));
		DELAY(100);
		/* enable FDC, but defer interrupts a moment */
		fdout_wr(fdc, fdc->fdout & ~FDO_FDMAEN);
	}
	DELAY(100);
	fdout_wr(fdc, fdc->fdout);

	/* XXX after a reset, silently believe the FDC will accept commands */
	if (fdc_cmd(fdc, 3, NE7CMD_SPECIFY, spec1, spec2, 0))
		device_printf(fdc->fdc_dev, " SPECIFY failed in reset\n");

	if (fdc->fdct == FDC_ENHANCED) {
		if (fdc_cmd(fdc, 4,
		    I8207X_CONFIG,
		    0,
		    /* 0x40 | */		/* Enable Implied Seek -
						 * breaks 2step! */
		    0x10 |			/* Polling disabled */
		    (fifo_threshold - 1),	/* Fifo threshold */
		    0x00,			/* Precomp track */
		    0))
			device_printf(fdc->fdc_dev,
			    " CONFIGURE failed in reset\n");
		if (debugflags & 1) {
			if (fdc_cmd(fdc, 1,
			    I8207X_DUMPREG,
			    10, &r[0], &r[1], &r[2], &r[3], &r[4],
			    &r[5], &r[6], &r[7], &r[8], &r[9]))
				device_printf(fdc->fdc_dev,
				    " DUMPREG failed in reset\n");
			for (i = 0; i < 10; i++)
				printf(" %02x", r[i]);
			printf("\n");
		}
	}
}