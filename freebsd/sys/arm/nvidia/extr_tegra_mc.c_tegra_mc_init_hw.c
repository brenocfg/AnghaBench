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
struct tegra_mc_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MC_INTMASK ; 
 int /*<<< orphan*/  MC_INTSTATUS ; 
 int /*<<< orphan*/  MC_INT_INT_MASK ; 
 int /*<<< orphan*/  WR4 (struct tegra_mc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tegra_mc_init_hw(struct tegra_mc_softc *sc)
{

	/* Disable and acknowledge all interrupts */
	WR4(sc, MC_INTMASK, 0);
	WR4(sc, MC_INTSTATUS, MC_INT_INT_MASK);
}