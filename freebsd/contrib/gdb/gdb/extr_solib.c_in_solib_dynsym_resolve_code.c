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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int TARGET_SO_IN_DYNSYM_RESOLVE_CODE (int /*<<< orphan*/ ) ; 

int
in_solib_dynsym_resolve_code (CORE_ADDR pc)
{
  return TARGET_SO_IN_DYNSYM_RESOLVE_CODE (pc);
}