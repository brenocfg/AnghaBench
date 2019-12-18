#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct fwohci_softc {scalar_t__ config_rom; TYPE_2__* crom_src_buf; } ;
struct TYPE_3__ {int generation; } ;
struct crom_src {TYPE_1__ businfo; } ;
struct TYPE_4__ {struct crom_src src; } ;

/* Variables and functions */
 int /*<<< orphan*/  CROMSIZE ; 
 scalar_t__ bcmp (void*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crom_load (struct crom_src*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dcons_crom (struct fwohci_softc*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  fw_reset_crom (struct fwohci_softc*) ; 
 void* malloc (int /*<<< orphan*/ ) ; 

void
fw_crom(struct fwohci_softc *sc)
{
	struct crom_src *src;
	void *newrom;

	fw_reset_crom(sc);
	dcons_crom(sc);

	newrom = malloc(CROMSIZE);
	src = &sc->crom_src_buf->src;
	crom_load(src, (uint32_t *)newrom, CROMSIZE);
	if (bcmp(newrom, sc->config_rom, CROMSIZE) != 0) {
		/* Bump generation and reload. */
		src->businfo.generation++;

		/* Handle generation count wraps. */
		if (src->businfo.generation < 2)
			src->businfo.generation = 2;

		/* Recalculate CRC to account for generation change. */
		crom_load(src, (uint32_t *)newrom, CROMSIZE);
		bcopy(newrom, (void *)sc->config_rom, CROMSIZE);
	}
	free(newrom);
}