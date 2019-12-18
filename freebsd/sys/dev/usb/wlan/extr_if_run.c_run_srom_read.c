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
typedef  int /*<<< orphan*/  uint16_t ;
struct run_softc {int (* sc_srom_read ) (struct run_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int stub1 (struct run_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline int
run_srom_read(struct run_softc *sc, uint16_t addr, uint16_t *val)
{
	/* either eFUSE ROM or EEPROM */
	return sc->sc_srom_read(sc, addr, val);
}