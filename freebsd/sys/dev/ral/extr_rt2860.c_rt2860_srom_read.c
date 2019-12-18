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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct rt2860_softc {int /*<<< orphan*/  (* sc_srom_read ) (struct rt2860_softc*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct rt2860_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline uint16_t
rt2860_srom_read(struct rt2860_softc *sc, uint8_t addr)
{
	/* either eFUSE ROM or EEPROM */
	return sc->sc_srom_read(sc, addr);
}