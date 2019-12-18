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
struct rk_cru_softc {intptr_t reset_num; int reset_offset; int /*<<< orphan*/  mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CCU_READ4 (struct rk_cru_softc*,int) ; 
 int ENXIO ; 
 struct rk_cru_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
rk_cru_reset_is_asserted(device_t dev, intptr_t id, bool *reset)
{
	struct rk_cru_softc *sc;
	uint32_t reg;
	int bit;
	uint32_t val;

	sc = device_get_softc(dev);

	if (id > sc->reset_num)
		return (ENXIO);
	reg = sc->reset_offset + id / 16 * 4;
	bit = id % 16;

	mtx_lock(&sc->mtx);
	val = CCU_READ4(sc, reg);
	mtx_unlock(&sc->mtx);

	*reset = false;
	if (val & (1 << bit))
		*reset = true;

	return (0);
}