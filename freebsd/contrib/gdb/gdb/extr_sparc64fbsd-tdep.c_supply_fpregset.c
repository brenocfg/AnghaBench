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
 int /*<<< orphan*/  sparc64_supply_fpregset (int /*<<< orphan*/ ,int,void const*) ; 

void
supply_fpregset (const void *fpregs)
{
  sparc64_supply_fpregset (current_regcache, -1, fpregs);
}