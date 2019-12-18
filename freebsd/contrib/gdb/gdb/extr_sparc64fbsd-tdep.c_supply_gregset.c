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
 int /*<<< orphan*/  current_regcache ; 
 int /*<<< orphan*/  sparc64_supply_gregset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,void const*) ; 
 int /*<<< orphan*/  sparc64fbsd_gregset ; 

void
supply_gregset (const void *gregs)
{
  sparc64_supply_gregset (&sparc64fbsd_gregset, current_regcache, -1, gregs);
}