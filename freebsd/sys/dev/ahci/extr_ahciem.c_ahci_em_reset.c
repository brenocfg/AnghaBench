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
struct ahci_enclosure {int channels; int /*<<< orphan*/  r_memc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int AHCI_EM_RST ; 
 int ATA_INL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATA_OUTL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  ahci_em_setleds (int /*<<< orphan*/ ,int) ; 
 struct ahci_enclosure* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
ahci_em_reset(device_t dev)
{
	struct ahci_enclosure *enc;
	int i, timeout;

	enc = device_get_softc(dev);
	ATA_OUTL(enc->r_memc, 0, AHCI_EM_RST);
	timeout = 1000;
	while ((ATA_INL(enc->r_memc, 0) & AHCI_EM_RST) &&
	    --timeout > 0)
		DELAY(1000);
	if (timeout == 0) {
		device_printf(dev, "EM timeout\n");
		return (1);
	}
	for (i = 0; i < enc->channels; i++)
		ahci_em_setleds(dev, i);
	return (0);
}