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
 int /*<<< orphan*/  add_core_fns (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_toc_address ; 
 int /*<<< orphan*/  rs6000_core_fns ; 
 int /*<<< orphan*/  rs6000_find_toc_address_hook ; 
 int /*<<< orphan*/  rs6000_set_host_arch_hook ; 
 int /*<<< orphan*/  set_host_arch ; 

void
_initialize_core_rs6000 (void)
{
  /* Initialize hook in rs6000-tdep.c for determining the TOC address when
     calling functions in the inferior.  */
  rs6000_find_toc_address_hook = find_toc_address;

  /* Initialize hook in rs6000-tdep.c to set the current architecture when
     starting a child process. */
  rs6000_set_host_arch_hook = set_host_arch;

  add_core_fns (&rs6000_core_fns);
}