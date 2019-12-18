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
struct regset {int dummy; } ;
struct regcache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sparc32_supply_fpregset (struct regcache*,int,void const*) ; 

__attribute__((used)) static void
sparc32nbsd_supply_fpregset (const struct regset *regset,
			     struct regcache *regcache,
			     int regnum, const void *fpregs, size_t len)
{
  sparc32_supply_fpregset (regcache, regnum, fpregs);
}