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

__attribute__((used)) static int
osf_in_dynsym_resolve_code (CORE_ADDR pc)
{
  /* This function currently always return False. This is a temporary
     solution which only consequence is to introduce a minor incovenience
     for the user: When stepping inside a subprogram located in a shared
     library, gdb might stop inside the dynamic loader code instead of
     inside the subprogram itself. See the explanations in infrun.c about
     the IN_SOLIB_DYNSYM_RESOLVE_CODE macro for more details. */
  return 0;
}