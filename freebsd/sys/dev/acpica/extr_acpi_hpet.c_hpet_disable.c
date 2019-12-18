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
typedef  int /*<<< orphan*/  uint32_t ;
struct hpet_softc {int /*<<< orphan*/  mem_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPET_CNF_ENABLE ; 
 int /*<<< orphan*/  HPET_CONFIG ; 
 int /*<<< orphan*/  bus_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hpet_disable(struct hpet_softc *sc)
{
	uint32_t val;

	val = bus_read_4(sc->mem_res, HPET_CONFIG);
	val &= ~HPET_CNF_ENABLE;
	bus_write_4(sc->mem_res, HPET_CONFIG, val);
}