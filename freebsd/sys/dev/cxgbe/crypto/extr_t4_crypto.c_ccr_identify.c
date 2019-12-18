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
struct adapter {int cryptocaps; } ;
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int FW_CAPS_CONFIG_CRYPTO_LOOKASIDE ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * device_find_child (int /*<<< orphan*/ ,char*,int) ; 
 struct adapter* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ccr_identify(driver_t *driver, device_t parent)
{
	struct adapter *sc;

	sc = device_get_softc(parent);
	if (sc->cryptocaps & FW_CAPS_CONFIG_CRYPTO_LOOKASIDE &&
	    device_find_child(parent, "ccr", -1) == NULL)
		device_add_child(parent, "ccr", -1);
}