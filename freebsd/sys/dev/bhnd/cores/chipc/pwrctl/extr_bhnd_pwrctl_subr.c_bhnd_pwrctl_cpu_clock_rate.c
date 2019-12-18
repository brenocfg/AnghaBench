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
struct bhnd_chipid {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  bhnd_pwrctl_clock_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bhnd_pwrctl_cpu_clkreg_m (struct bhnd_chipid const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

uint32_t
bhnd_pwrctl_cpu_clock_rate(const struct bhnd_chipid *cid,
    uint32_t pll_type, uint32_t n, uint32_t m)
{
	KASSERT(bhnd_pwrctl_cpu_clkreg_m(cid, pll_type, NULL) != 0,
	    ("can't compute clock rate on fixed clock"));

	return (bhnd_pwrctl_clock_rate(pll_type, n, m));
}