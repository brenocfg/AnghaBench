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
struct padctl_softc {int dummy; } ;
struct padctl_lane {int mask; int shift; int mux_idx; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int RD4 (struct padctl_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR4 (struct padctl_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
config_lane(struct padctl_softc *sc, struct padctl_lane *lane)
{
	uint32_t reg;

	reg = RD4(sc, lane->reg);
	reg &= ~(lane->mask << lane->shift);
	reg |=  (lane->mux_idx & lane->mask) << lane->shift;
	WR4(sc, lane->reg, reg);
	return (0);
}