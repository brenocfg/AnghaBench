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
struct twa_softc {int /*<<< orphan*/  ctlr_handle; int /*<<< orphan*/ * watchdog_callout; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  TW_INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  TW_CL_MESSAGE_SOURCE_FREEBSD_DRIVER ; 
 int /*<<< orphan*/  TW_CL_SEVERITY_ERROR_STRING ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 struct twa_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_cl_shutdown_ctlr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_osli_dbg_dprintf (int,struct twa_softc*,char*) ; 
 int /*<<< orphan*/  tw_osli_printf (struct twa_softc*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twa_teardown_intr (struct twa_softc*) ; 

__attribute__((used)) static TW_INT32
twa_shutdown(device_t dev)
{
	struct twa_softc	*sc = device_get_softc(dev);
	TW_INT32		error = 0;

	tw_osli_dbg_dprintf(3, sc, "entered");

	/* Disconnect interrupts. */
	error = twa_teardown_intr(sc);

	/* Stop watchdog task. */
	callout_drain(&(sc->watchdog_callout[0]));
	callout_drain(&(sc->watchdog_callout[1]));

	/* Disconnect from the controller. */
	if ((error = tw_cl_shutdown_ctlr(&(sc->ctlr_handle), 0))) {
		tw_osli_printf(sc, "error = %d",
			TW_CL_SEVERITY_ERROR_STRING,
			TW_CL_MESSAGE_SOURCE_FREEBSD_DRIVER,
			0x2015,
			"Failed to shutdown Common Layer/controller",
			error);
	}
	return(error);
}