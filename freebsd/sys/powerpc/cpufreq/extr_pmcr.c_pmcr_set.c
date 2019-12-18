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
struct cf_setting {scalar_t__* spec; } ;
typedef  long register_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 long PMCR_LOWERPS_MASK ; 
 long PMCR_LOWERPS_SHIFT ; 
 long PMCR_UPPERPS_MASK ; 
 long PMCR_UPPERPS_SHIFT ; 
 long PMCR_VERSION_1 ; 
 int /*<<< orphan*/  SPR_PMCR ; 
 int /*<<< orphan*/  isync () ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,long) ; 
 scalar_t__ npstates ; 
 int /*<<< orphan*/  powerpc_sync () ; 

__attribute__((used)) static int
pmcr_set(device_t dev, const struct cf_setting *set)
{
	register_t pmcr;
	
	if (set == NULL)
		return (EINVAL);

	if (set->spec[1] < 0 || set->spec[1] >= npstates)
		return (EINVAL);

	pmcr = ((long)set->spec[0] << PMCR_LOWERPS_SHIFT) & PMCR_LOWERPS_MASK;
	pmcr |= ((long)set->spec[0] << PMCR_UPPERPS_SHIFT) & PMCR_UPPERPS_MASK;
	pmcr |= PMCR_VERSION_1;

	mtspr(SPR_PMCR, pmcr);
	powerpc_sync(); isync();

	return (0);
}