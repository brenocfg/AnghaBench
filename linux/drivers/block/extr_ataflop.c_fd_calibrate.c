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
struct TYPE_4__ {scalar_t__ track; int steprate; } ;
struct TYPE_3__ {scalar_t__ fdc_speed; } ;

/* Variables and functions */
 scalar_t__ ATARIHW_PRESENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*) ; 
 int FDCCMD_RESTORE ; 
 int /*<<< orphan*/  FDCREG_CMD ; 
 int /*<<< orphan*/  FDCSPEED ; 
 int /*<<< orphan*/  FDC_WRITE (int /*<<< orphan*/ ,int) ; 
 int MotorOn ; 
 int NeedSeek ; 
 int /*<<< orphan*/  SET_IRQ_HANDLER (int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 
 TYPE_2__ SUD ; 
 TYPE_1__ dma_wd ; 
 int /*<<< orphan*/  fd_calibrate_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_timeout () ; 

__attribute__((used)) static void fd_calibrate( void )
{
	if (SUD.track >= 0) {
		fd_calibrate_done( 0 );
		return;
	}

	if (ATARIHW_PRESENT(FDCSPEED))
		dma_wd.fdc_speed = 0; 	/* always seek with 8 Mhz */;
	DPRINT(("fd_calibrate\n"));
	SET_IRQ_HANDLER( fd_calibrate_done );
	/* we can't verify, since the speed may be incorrect */
	FDC_WRITE( FDCREG_CMD, FDCCMD_RESTORE | SUD.steprate );

	NeedSeek = 1;
	MotorOn = 1;
	start_timeout();
	/* wait for IRQ */
}