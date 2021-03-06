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
struct sc_info {int /*<<< orphan*/  nabmbarh; int /*<<< orphan*/  nabmbart; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_space_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
ich_wr(struct sc_info *sc, int regno, uint32_t data, int size)
{
	switch (size) {
	case 1:
		bus_space_write_1(sc->nabmbart, sc->nabmbarh, regno, data);
		break;
	case 2:
		bus_space_write_2(sc->nabmbart, sc->nabmbarh, regno, data);
		break;
	case 4:
		bus_space_write_4(sc->nabmbart, sc->nabmbarh, regno, data);
		break;
	}
}