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
typedef  int /*<<< orphan*/  v ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int u_long ;
struct uio {int uio_offset; int uio_resid; } ;
struct terasic_mtl_softc {int /*<<< orphan*/  mtl_text_res; } ;
struct cdev {struct terasic_mtl_softc* si_drv1; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  bus_write_2 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int rman_get_size (int /*<<< orphan*/ ) ; 
 int uiomove (int /*<<< orphan*/ *,int,struct uio*) ; 

__attribute__((used)) static int
terasic_mtl_text_write(struct cdev *dev, struct uio *uio, int flag)
{
	struct terasic_mtl_softc *sc;
	u_long offset, size;
	uint16_t v;
	int error;

	if (uio->uio_offset < 0 || uio->uio_offset % 2 != 0 ||
	    uio->uio_resid % 2 != 0)
		return (ENODEV);
	sc = dev->si_drv1;
	size = rman_get_size(sc->mtl_text_res);
	error = 0;
	while (uio->uio_resid > 0) {
		offset = uio->uio_offset;
		if (offset + sizeof(v) > size)
			return (ENODEV);
		error = uiomove(&v, sizeof(v), uio);
		if (error)
			return (error);
		bus_write_2(sc->mtl_text_res, offset, v);
	}
	return (error);
}