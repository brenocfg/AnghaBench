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
struct sc_info {int /*<<< orphan*/  nabmbarh; int /*<<< orphan*/  nabmbart; } ;

/* Variables and functions */
 int bus_space_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int bus_space_read_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __inline uint32_t
ich_rd(struct sc_info *sc, int regno, int size)
{
	switch (size) {
	case 1:
		return (bus_space_read_1(sc->nabmbart, sc->nabmbarh, regno));
	case 2:
		return (bus_space_read_2(sc->nabmbart, sc->nabmbarh, regno));
	case 4:
		return (bus_space_read_4(sc->nabmbart, sc->nabmbarh, regno));
	default:
		return (0xffffffff);
	}
}