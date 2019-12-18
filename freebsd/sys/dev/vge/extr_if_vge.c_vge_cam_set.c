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
typedef  int uint8_t ;
struct vge_softc {int vge_camidx; int /*<<< orphan*/  vge_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_CLRBIT_1 (struct vge_softc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int CSR_READ_1 (struct vge_softc*,scalar_t__) ; 
 int /*<<< orphan*/  CSR_SETBIT_1 (struct vge_softc*,scalar_t__,int) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct vge_softc*,scalar_t__,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int EIO ; 
 int ENOSPC ; 
 int ETHER_ADDR_LEN ; 
 scalar_t__ VGE_CAM0 ; 
 scalar_t__ VGE_CAMADDR ; 
 int VGE_CAMADDR_ENABLE ; 
 scalar_t__ VGE_CAMCTL ; 
 int /*<<< orphan*/  VGE_CAMCTL_PAGESEL ; 
 int VGE_CAMCTL_WRITE ; 
 int VGE_CAM_MAXADDRS ; 
 int VGE_PAGESEL_CAMDATA ; 
 int VGE_PAGESEL_CAMMASK ; 
 int VGE_PAGESEL_MAR ; 
 int VGE_TIMEOUT ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
vge_cam_set(struct vge_softc *sc, uint8_t *addr)
{
	int i, error = 0;

	if (sc->vge_camidx == VGE_CAM_MAXADDRS)
		return (ENOSPC);

	/* Select the CAM data page. */
	CSR_CLRBIT_1(sc, VGE_CAMCTL, VGE_CAMCTL_PAGESEL);
	CSR_SETBIT_1(sc, VGE_CAMCTL, VGE_PAGESEL_CAMDATA);

	/* Set the filter entry we want to update and enable writing. */
	CSR_WRITE_1(sc, VGE_CAMADDR, VGE_CAMADDR_ENABLE|sc->vge_camidx);

	/* Write the address to the CAM registers */
	for (i = 0; i < ETHER_ADDR_LEN; i++)
		CSR_WRITE_1(sc, VGE_CAM0 + i, addr[i]);

	/* Issue a write command. */
	CSR_SETBIT_1(sc, VGE_CAMCTL, VGE_CAMCTL_WRITE);

	/* Wake for it to clear. */
	for (i = 0; i < VGE_TIMEOUT; i++) {
		DELAY(1);
		if ((CSR_READ_1(sc, VGE_CAMCTL) & VGE_CAMCTL_WRITE) == 0)
			break;
	}

	if (i == VGE_TIMEOUT) {
		device_printf(sc->vge_dev, "setting CAM filter failed\n");
		error = EIO;
		goto fail;
	}

	/* Select the CAM mask page. */
	CSR_CLRBIT_1(sc, VGE_CAMCTL, VGE_CAMCTL_PAGESEL);
	CSR_SETBIT_1(sc, VGE_CAMCTL, VGE_PAGESEL_CAMMASK);

	/* Set the mask bit that enables this filter. */
	CSR_SETBIT_1(sc, VGE_CAM0 + (sc->vge_camidx/8),
	    1<<(sc->vge_camidx & 7));

	sc->vge_camidx++;

fail:
	/* Turn off access to CAM. */
	CSR_WRITE_1(sc, VGE_CAMADDR, 0);
	CSR_CLRBIT_1(sc, VGE_CAMCTL, VGE_CAMCTL_PAGESEL);
	CSR_SETBIT_1(sc, VGE_CAMCTL, VGE_PAGESEL_MAR);

	return (error);
}