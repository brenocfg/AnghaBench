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
typedef  unsigned long CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  supply_register_by_name (char*,unsigned long*) ; 

__attribute__((used)) static void
arm_set_pc (CORE_ADDR pc)
{
  unsigned long newpc = pc;
  supply_register_by_name ("pc", &newpc);
}