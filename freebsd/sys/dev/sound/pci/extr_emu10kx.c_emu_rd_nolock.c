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
struct emu_sc_info {int /*<<< orphan*/  sh; int /*<<< orphan*/  st; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int bus_space_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int bus_space_read_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static uint32_t
emu_rd_nolock(struct emu_sc_info *sc, unsigned int regno, unsigned int size)
{

	KASSERT(sc != NULL, ("emu_rd: NULL sc"));
	switch (size) {
	case 1:
		return (bus_space_read_1(sc->st, sc->sh, regno));
	case 2:
		return (bus_space_read_2(sc->st, sc->sh, regno));
	case 4:
		return (bus_space_read_4(sc->st, sc->sh, regno));
	}
	return (0xffffffff);
}