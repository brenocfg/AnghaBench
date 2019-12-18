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
struct regset {int /*<<< orphan*/  descr; } ;
struct regcache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sparc64_supply_gregset (int /*<<< orphan*/ ,struct regcache*,int,void const*) ; 

__attribute__((used)) static void
sparc64fbsd_supply_gregset (const struct regset *regset,
			    struct regcache *regcache,
			    int regnum, const void *gregs, size_t len)
{
  sparc64_supply_gregset (regset->descr, regcache, regnum, gregs);
}