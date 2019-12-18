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
struct twa_softc {scalar_t__ open; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  scalar_t__ TW_INT32 ;

/* Variables and functions */
 scalar_t__ EBUSY ; 
 int /*<<< orphan*/  TW_CL_MESSAGE_SOURCE_FREEBSD_DRIVER ; 
 int /*<<< orphan*/  TW_CL_SEVERITY_ERROR_STRING ; 
 struct twa_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_osli_dbg_dprintf (int,struct twa_softc*,char*) ; 
 int /*<<< orphan*/  tw_osli_free_resources (struct twa_softc*) ; 
 int /*<<< orphan*/  tw_osli_printf (struct twa_softc*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,scalar_t__) ; 
 scalar_t__ twa_shutdown (int /*<<< orphan*/ ) ; 

__attribute__((used)) static TW_INT32
twa_detach(device_t dev)
{
	struct twa_softc	*sc = device_get_softc(dev);
	TW_INT32		error;

	tw_osli_dbg_dprintf(3, sc, "entered");

	error = EBUSY;
	if (sc->open) {
		tw_osli_printf(sc, "error = %d",
			TW_CL_SEVERITY_ERROR_STRING,
			TW_CL_MESSAGE_SOURCE_FREEBSD_DRIVER,
			0x2014,
			"Device open",
			error);
		goto out;
	}

	/* Shut the controller down. */
	if ((error = twa_shutdown(dev)))
		goto out;

	/* Free all resources associated with this controller. */
	tw_osli_free_resources(sc);
	error = 0;

out:
	return(error);
}