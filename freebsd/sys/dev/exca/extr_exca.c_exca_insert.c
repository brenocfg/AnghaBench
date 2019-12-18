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
struct exca_softc {int /*<<< orphan*/  dev; int /*<<< orphan*/  pccarddev; } ;

/* Variables and functions */
 scalar_t__ CARD_ATTACH_CARD (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

void
exca_insert(struct exca_softc *exca)
{
	if (device_is_attached(exca->pccarddev)) {
		if (CARD_ATTACH_CARD(exca->pccarddev) != 0)
			device_printf(exca->dev,
			    "PC Card card activation failed\n");
	} else {
		device_printf(exca->dev,
		    "PC Card inserted, but no pccard bus.\n");
	}
}