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

/* Variables and functions */
 int /*<<< orphan*/ * sparc32_collect_fpregset ; 
 int /*<<< orphan*/ * sparc32_collect_gregset ; 
 int /*<<< orphan*/ * sparc32_fpregset_supplies_p ; 
 int /*<<< orphan*/ * sparc32_gregset_supplies_p ; 
 int /*<<< orphan*/  sparc32_sunos4_gregset ; 
 int /*<<< orphan*/ * sparc32_supply_fpregset ; 
 int /*<<< orphan*/ * sparc32_supply_gregset ; 
 int /*<<< orphan*/ * sparc_collect_fpregset ; 
 int /*<<< orphan*/ * sparc_collect_gregset ; 
 int /*<<< orphan*/ * sparc_fpregset_supplies_p ; 
 int /*<<< orphan*/ * sparc_gregset ; 
 int /*<<< orphan*/ * sparc_gregset_supplies_p ; 
 int /*<<< orphan*/ * sparc_supply_fpregset ; 
 int /*<<< orphan*/ * sparc_supply_gregset ; 

void
_initialize_sparc_nat (void)
{
  /* Deafult to using SunOS 4 register sets.  */
  if (sparc_gregset == NULL)
    sparc_gregset = &sparc32_sunos4_gregset;
  if (sparc_supply_gregset == NULL)
    sparc_supply_gregset = sparc32_supply_gregset;
  if (sparc_collect_gregset == NULL)
    sparc_collect_gregset = sparc32_collect_gregset;
  if (sparc_supply_fpregset == NULL)
    sparc_supply_fpregset = sparc32_supply_fpregset;
  if (sparc_collect_fpregset == NULL)
    sparc_collect_fpregset = sparc32_collect_fpregset;
  if (sparc_gregset_supplies_p == NULL)
    sparc_gregset_supplies_p = sparc32_gregset_supplies_p;
  if (sparc_fpregset_supplies_p == NULL)
    sparc_fpregset_supplies_p = sparc32_fpregset_supplies_p;
}