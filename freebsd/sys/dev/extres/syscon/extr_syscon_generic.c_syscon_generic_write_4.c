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
struct syscon_generic_softc {int /*<<< orphan*/  mem_res; } ;
struct syscon {int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  bus_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYSCON_LOCK (struct syscon_generic_softc*) ; 
 int /*<<< orphan*/  SYSCON_UNLOCK (struct syscon_generic_softc*) ; 
 int /*<<< orphan*/  bus_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct syscon_generic_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
syscon_generic_write_4(struct syscon *syscon, bus_size_t offset, uint32_t val)
{
	struct syscon_generic_softc *sc;

	sc = device_get_softc(syscon->pdev);

	SYSCON_LOCK(sc);
	bus_write_4(sc->mem_res, offset, val);
	SYSCON_UNLOCK(sc);
	return (0);
}