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
struct TYPE_2__ {int /*<<< orphan*/  track; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*) ; 
 int /*<<< orphan*/  FDCCMD_SEEK ; 
 int /*<<< orphan*/  FDCREG_CMD ; 
 int /*<<< orphan*/  FDCREG_DATA ; 
 int /*<<< orphan*/  FDC_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MotorOn ; 
 int /*<<< orphan*/  NeedSeek ; 
 int /*<<< orphan*/  SET_IRQ_HANDLER (int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 
 TYPE_1__ SUD ; 
 int /*<<< orphan*/  finish_fdc_done (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_timeout () ; 

__attribute__((used)) static void finish_fdc( void )
{
	if (!NeedSeek) {
		finish_fdc_done( 0 );
	}
	else {
		DPRINT(("finish_fdc: dummy seek started\n"));
		FDC_WRITE (FDCREG_DATA, SUD.track);
		SET_IRQ_HANDLER( finish_fdc_done );
		FDC_WRITE (FDCREG_CMD, FDCCMD_SEEK);
		MotorOn = 1;
		start_timeout();
		/* we must wait for the IRQ here, because the ST-DMA
		   is released immediately afterwards and the interrupt
		   may be delivered to the wrong driver. */
	  }
}