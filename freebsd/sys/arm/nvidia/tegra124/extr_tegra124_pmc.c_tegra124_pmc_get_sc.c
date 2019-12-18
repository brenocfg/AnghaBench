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
struct tegra124_pmc_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  panic (char*) ; 
 struct tegra124_pmc_softc* pmc_sc ; 

__attribute__((used)) static inline struct tegra124_pmc_softc *
tegra124_pmc_get_sc(void)
{
	if (pmc_sc == NULL)
		panic("To early call to Tegra PMC driver.\n");
	return (pmc_sc);
}