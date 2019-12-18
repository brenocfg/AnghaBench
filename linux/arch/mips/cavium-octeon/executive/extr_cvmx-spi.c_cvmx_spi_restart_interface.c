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
typedef  size_t cvmx_spi_mode_t ;
struct TYPE_2__ {int /*<<< orphan*/  interface_up_cb; int /*<<< orphan*/  calendar_sync_cb; int /*<<< orphan*/  training_cb; int /*<<< orphan*/  clock_detect_cb; int /*<<< orphan*/  reset_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  INVOKE_CB (int /*<<< orphan*/ ,int,size_t,...) ; 
 int /*<<< orphan*/  OCTEON_CN38XX ; 
 int /*<<< orphan*/  OCTEON_CN58XX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__ cvmx_spi_callbacks ; 
 int /*<<< orphan*/ * modes ; 

int cvmx_spi_restart_interface(int interface, cvmx_spi_mode_t mode, int timeout)
{
	int res = -1;

	if (!(OCTEON_IS_MODEL(OCTEON_CN38XX) || OCTEON_IS_MODEL(OCTEON_CN58XX)))
		return res;

	cvmx_dprintf("SPI%d: Restart %s\n", interface, modes[mode]);

	/* Callback to perform SPI4 reset */
	INVOKE_CB(cvmx_spi_callbacks.reset_cb, interface, mode);

	/* NOTE: Calendar setup is not performed during restart */
	/*	 Refer to cvmx_spi_start_interface() for the full sequence */

	/* Callback to perform clock detection */
	INVOKE_CB(cvmx_spi_callbacks.clock_detect_cb, interface, mode, timeout);

	/* Callback to perform SPI4 link training */
	INVOKE_CB(cvmx_spi_callbacks.training_cb, interface, mode, timeout);

	/* Callback to perform calendar sync */
	INVOKE_CB(cvmx_spi_callbacks.calendar_sync_cb, interface, mode,
		  timeout);

	/* Callback to handle interface coming up */
	INVOKE_CB(cvmx_spi_callbacks.interface_up_cb, interface, mode);

	return res;
}