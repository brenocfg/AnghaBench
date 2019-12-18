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
struct zy7_devcfg_softc {int /*<<< orphan*/  dma_tag; scalar_t__ is_open; } ;
struct thread {int dummy; } ;
struct cdev {struct zy7_devcfg_softc* si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVCFG_SC_LOCK (struct zy7_devcfg_softc*) ; 
 int /*<<< orphan*/  DEVCFG_SC_UNLOCK (struct zy7_devcfg_softc*) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zy7_en_level_shifters ; 
 int /*<<< orphan*/  zy7_slcr_postload_pl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zy7_devcfg_close(struct cdev *dev, int fflag, int devtype, struct thread *td)
{
	struct zy7_devcfg_softc *sc = dev->si_drv1;

	DEVCFG_SC_LOCK(sc);
	sc->is_open = 0;
	bus_dma_tag_destroy(sc->dma_tag);
	DEVCFG_SC_UNLOCK(sc);

	zy7_slcr_postload_pl(zy7_en_level_shifters);

	return (0);
}