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
struct atpic_softc {int /*<<< orphan*/ * sc_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_read_1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline uint8_t
atpic_read(struct atpic_softc *sc, int icu, int ofs)
{
	uint8_t val;

	val = bus_read_1(sc->sc_res[icu], ofs);
	return (val);
}