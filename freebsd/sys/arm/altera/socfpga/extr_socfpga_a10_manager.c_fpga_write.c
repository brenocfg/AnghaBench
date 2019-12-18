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
typedef  int uint32_t ;
struct uio {int uio_resid; } ;
struct fpgamgr_a10_softc {int /*<<< orphan*/  bsh_data; int /*<<< orphan*/  bst_data; } ;
struct cdev {struct fpgamgr_a10_softc* si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  uiomove (int*,int,struct uio*) ; 

__attribute__((used)) static int
fpga_write(struct cdev *dev, struct uio *uio, int ioflag)
{
	struct fpgamgr_a10_softc *sc;
	uint32_t buffer;

	sc = dev->si_drv1;

	/*
	 * Step 9.
	 * Device supports 4-byte writes only.
	 */

	while (uio->uio_resid >= 4) {
		uiomove(&buffer, 4, uio);
		bus_space_write_4(sc->bst_data, sc->bsh_data,
		    0x0, buffer);
	}

	switch (uio->uio_resid) {
	case 3:
		uiomove(&buffer, 3, uio);
		buffer &= 0xffffff;
		bus_space_write_4(sc->bst_data, sc->bsh_data,
		    0x0, buffer);
		break;
	case 2:
		uiomove(&buffer, 2, uio);
		buffer &= 0xffff;
		bus_space_write_4(sc->bst_data, sc->bsh_data,
		    0x0, buffer);
		break;
	case 1:
		uiomove(&buffer, 1, uio);
		buffer &= 0xff;
		bus_space_write_4(sc->bst_data, sc->bsh_data,
		    0x0, buffer);
		break;
	default:
		break;
	};

	return (0);
}