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
typedef  int u_int32_t ;
struct sc_info {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  PCIR_DSXGCTRL ; 
 scalar_t__ ds_cdbusy (struct sc_info*,int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static u_int32_t
ds_initcd(kobj_t obj, void *devinfo)
{
	struct sc_info *sc = (struct sc_info *)devinfo;
	u_int32_t x;

	x = pci_read_config(sc->dev, PCIR_DSXGCTRL, 1);
	if (x & 0x03) {
		pci_write_config(sc->dev, PCIR_DSXGCTRL, x & ~0x03, 1);
		pci_write_config(sc->dev, PCIR_DSXGCTRL, x | 0x03, 1);
		pci_write_config(sc->dev, PCIR_DSXGCTRL, x & ~0x03, 1);
		/*
		 * The YMF740 on some Intel motherboards requires a pretty
		 * hefty delay after this reset for some reason...  Otherwise:
		 * "pcm0: ac97 codec init failed"
		 * Maybe this is needed for all YMF740's?
		 * 400ms and 500ms here seem to work, 300ms does not.
		 *
		 * do it for all chips -cg
		 */
		DELAY(500000);
	}

	return ds_cdbusy(sc, 0)? 0 : 1;
}