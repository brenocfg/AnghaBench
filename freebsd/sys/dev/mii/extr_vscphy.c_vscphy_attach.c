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
struct vscphy_softc {int /*<<< orphan*/  mii_sc; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MIIF_NOMANPAUSE ; 
 struct vscphy_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_phy_dev_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mii_phy_setmedia (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vscphy_fdt_get_config (struct vscphy_softc*) ; 
 int /*<<< orphan*/  vscphy_funcs ; 

__attribute__((used)) static int
vscphy_attach(device_t dev)
{
	struct vscphy_softc *vsc;

	vsc = device_get_softc(dev);
	vsc->dev = dev;

#ifdef FDT
	vscphy_fdt_get_config(vsc);
#endif	

	mii_phy_dev_attach(dev, MIIF_NOMANPAUSE, &vscphy_funcs, 1);
	mii_phy_setmedia(&vsc->mii_sc);

	return (0);
}