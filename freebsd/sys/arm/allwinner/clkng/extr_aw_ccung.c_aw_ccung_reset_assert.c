#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct aw_ccung_softc {intptr_t nresets; int /*<<< orphan*/  mtx; TYPE_1__* resets; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {char* offset; int shift; } ;

/* Variables and functions */
 int CCU_READ4 (struct aw_ccung_softc*,char*) ; 
 int /*<<< orphan*/  CCU_WRITE4 (struct aw_ccung_softc*,char*,int) ; 
 struct aw_ccung_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,char*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
aw_ccung_reset_assert(device_t dev, intptr_t id, bool reset)
{
	struct aw_ccung_softc *sc;
	uint32_t val;

	sc = device_get_softc(dev);

	dprintf("%sassert reset id %ld\n", reset ? "" : "De", id);
	if (id >= sc->nresets || sc->resets[id].offset == 0)
		return (0);

	mtx_lock(&sc->mtx);
	val = CCU_READ4(sc, sc->resets[id].offset);
	dprintf("offset=%x Read %x\n", sc->resets[id].offset, val);
	if (reset)
		val &= ~(1 << sc->resets[id].shift);
	else
		val |= 1 << sc->resets[id].shift;
	dprintf("offset=%x Write %x\n", sc->resets[id].offset, val);
	CCU_WRITE4(sc, sc->resets[id].offset, val);
	mtx_unlock(&sc->mtx);

	return (0);
}