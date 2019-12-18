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
struct msk_softc {size_t msk_hw_id; int msk_hw_rev; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  desc ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 size_t CHIP_ID_YUKON_XL ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct msk_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ ,char*) ; 
 char** model_name ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,size_t,int) ; 

__attribute__((used)) static int
msk_probe(device_t dev)
{
	struct msk_softc *sc;
	char desc[100];

	sc = device_get_softc(device_get_parent(dev));
	/*
	 * Not much to do here. We always know there will be
	 * at least one GMAC present, and if there are two,
	 * mskc_attach() will create a second device instance
	 * for us.
	 */
	snprintf(desc, sizeof(desc),
	    "Marvell Technology Group Ltd. %s Id 0x%02x Rev 0x%02x",
	    model_name[sc->msk_hw_id - CHIP_ID_YUKON_XL], sc->msk_hw_id,
	    sc->msk_hw_rev);
	device_set_desc_copy(dev, desc);

	return (BUS_PROBE_DEFAULT);
}