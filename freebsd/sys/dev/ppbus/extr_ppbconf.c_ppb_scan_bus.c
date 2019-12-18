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
struct ppb_data {scalar_t__ state; scalar_t__ error; int /*<<< orphan*/  class_id; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PPB_COMPATIBLE ; 
 int /*<<< orphan*/  PPB_ECP ; 
 int /*<<< orphan*/  PPB_EPP ; 
 scalar_t__ PPB_ERROR ; 
 int PPB_EXTENSIBILITY_LINK ; 
 int /*<<< orphan*/  PPB_NIBBLE ; 
 scalar_t__ PPB_NOT_IEEE1284 ; 
 int /*<<< orphan*/  PPB_PS2 ; 
 int PPB_REQUEST_ID ; 
 int PPB_USE_RLE ; 
 scalar_t__ bootverbose ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int ppb_1284_negociate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ppb_1284_terminate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_pnp_detect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
ppb_scan_bus(device_t bus)
{
	struct ppb_data * ppb = (struct ppb_data *)device_get_softc(bus);
	int error = 0;

	/* try all IEEE1284 modes, for one device only
	 *
	 * XXX We should implement the IEEE1284.3 standard to detect
	 * daisy chained devices
	 */

	error = ppb_1284_negociate(bus, PPB_NIBBLE, PPB_REQUEST_ID);

	if ((ppb->state == PPB_ERROR) && (ppb->error == PPB_NOT_IEEE1284))
		goto end_scan;

	ppb_1284_terminate(bus);

	device_printf(bus, "IEEE1284 device found ");

	if (!(error = ppb_1284_negociate(bus, PPB_NIBBLE, 0))) {
		printf("/NIBBLE");
		ppb_1284_terminate(bus);
	}

	if (!(error = ppb_1284_negociate(bus, PPB_PS2, 0))) {
		printf("/PS2");
		ppb_1284_terminate(bus);
	}

	if (!(error = ppb_1284_negociate(bus, PPB_ECP, 0))) {
		printf("/ECP");
		ppb_1284_terminate(bus);
	}

	if (!(error = ppb_1284_negociate(bus, PPB_ECP, PPB_USE_RLE))) {
		printf("/ECP_RLE");
		ppb_1284_terminate(bus);
	}

	if (!(error = ppb_1284_negociate(bus, PPB_EPP, 0))) {
		printf("/EPP");
		ppb_1284_terminate(bus);
	}

	/* try more IEEE1284 modes */
	if (bootverbose) {
		if (!(error = ppb_1284_negociate(bus, PPB_NIBBLE,
				PPB_REQUEST_ID))) {
			printf("/NIBBLE_ID");
			ppb_1284_terminate(bus);
		}

		if (!(error = ppb_1284_negociate(bus, PPB_PS2,
				PPB_REQUEST_ID))) {
			printf("/PS2_ID");
			ppb_1284_terminate(bus);
		}

		if (!(error = ppb_1284_negociate(bus, PPB_ECP,
				PPB_REQUEST_ID))) {
			printf("/ECP_ID");
			ppb_1284_terminate(bus);
		}

		if (!(error = ppb_1284_negociate(bus, PPB_ECP,
				PPB_REQUEST_ID | PPB_USE_RLE))) {
			printf("/ECP_RLE_ID");
			ppb_1284_terminate(bus);
		}

		if (!(error = ppb_1284_negociate(bus, PPB_COMPATIBLE,
				PPB_EXTENSIBILITY_LINK))) {
			printf("/Extensibility Link");
			ppb_1284_terminate(bus);
		}
	}

	printf("\n");

	/* detect PnP devices */
	ppb->class_id = ppb_pnp_detect(bus);

	return (0);

end_scan:
	return (error);
}