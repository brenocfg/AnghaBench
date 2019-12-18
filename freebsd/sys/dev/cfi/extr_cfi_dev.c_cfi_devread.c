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
typedef  void* uint8_t ;
typedef  void* uint32_t ;
typedef  void* uint16_t ;
typedef  int u_int ;
struct uio {scalar_t__ uio_offset; scalar_t__ uio_resid; } ;
struct cfi_softc {scalar_t__ sc_size; int sc_width; scalar_t__ sc_writing; } ;
struct cdev {struct cfi_softc* si_drv1; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MIN (scalar_t__,int) ; 
 int cfi_block_finish (struct cfi_softc*) ; 
 void* cfi_read_raw (struct cfi_softc*,int) ; 
 int uiomove (void**,int /*<<< orphan*/ ,struct uio*) ; 

__attribute__((used)) static int
cfi_devread(struct cdev *dev, struct uio *uio, int ioflag)
{
	union {
		uint8_t		x8[4];
		uint16_t	x16[2];
		uint32_t	x32[1];
	} buf;
	struct cfi_softc *sc;
	u_int ofs;
	uint32_t val;
	int error;

	sc = dev->si_drv1;

	error = (sc->sc_writing) ? cfi_block_finish(sc) : 0;
	if (!error)
		error = (uio->uio_offset > sc->sc_size) ? EIO : 0;

	while (error == 0 && uio->uio_resid > 0 &&
	    uio->uio_offset < sc->sc_size) {
		ofs = uio->uio_offset;
		val = cfi_read_raw(sc, ofs);
		switch (sc->sc_width) {
		case 1:
			buf.x8[0] = val;
			break;
		case 2:
			buf.x16[0] = val;
			break;
		case 4:
			buf.x32[0] = val;
			break;
		}
		ofs &= sc->sc_width - 1;
		error = uiomove(buf.x8 + ofs,
		    MIN(uio->uio_resid, sc->sc_width - ofs), uio);
	}
	return (error);
}