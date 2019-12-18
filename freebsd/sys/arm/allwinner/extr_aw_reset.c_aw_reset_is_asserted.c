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
struct aw_reset_softc {int /*<<< orphan*/  mtx; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  RESET_OFFSET (intptr_t) ; 
 int RESET_READ (struct aw_reset_softc*,int /*<<< orphan*/ ) ; 
 int RESET_SHIFT (intptr_t) ; 
 struct aw_reset_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
aw_reset_is_asserted(device_t dev, intptr_t id, bool *reset)
{
	struct aw_reset_softc *sc;
	uint32_t reg_value;

	sc = device_get_softc(dev);

	mtx_lock(&sc->mtx);
	reg_value = RESET_READ(sc, RESET_OFFSET(id));
	mtx_unlock(&sc->mtx);

	*reset = (reg_value & (1 << RESET_SHIFT(id))) != 0 ? false : true;

	return (0);
}