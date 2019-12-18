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
 int /*<<< orphan*/  sparc64nbsd_collect_fpregset ; 
 int /*<<< orphan*/  sparc64nbsd_collect_gregset ; 
 int /*<<< orphan*/  sparc64nbsd_fpregset_supplies_p ; 
 int /*<<< orphan*/  sparc64nbsd_gregset_supplies_p ; 
 int /*<<< orphan*/  sparc64nbsd_supply_fpregset ; 
 int /*<<< orphan*/  sparc64nbsd_supply_gregset ; 
 int /*<<< orphan*/  sparc_collect_fpregset ; 
 int /*<<< orphan*/  sparc_collect_gregset ; 
 int /*<<< orphan*/  sparc_fpregset_supplies_p ; 
 int /*<<< orphan*/  sparc_gregset_supplies_p ; 
 int /*<<< orphan*/  sparc_supply_fpregset ; 
 int /*<<< orphan*/  sparc_supply_gregset ; 

void
_initialize_sparcnbsd_nat (void)
{
  sparc_supply_gregset = sparc64nbsd_supply_gregset;
  sparc_collect_gregset = sparc64nbsd_collect_gregset;
  sparc_supply_fpregset = sparc64nbsd_supply_fpregset;
  sparc_collect_fpregset = sparc64nbsd_collect_fpregset;
  sparc_gregset_supplies_p = sparc64nbsd_gregset_supplies_p;
  sparc_fpregset_supplies_p = sparc64nbsd_fpregset_supplies_p;
}