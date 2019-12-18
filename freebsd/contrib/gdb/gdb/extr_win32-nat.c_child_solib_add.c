#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct target_ops {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  load_addr; scalar_t__ name; int /*<<< orphan*/  objfile; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_map_over_sections (scalar_t__,int /*<<< orphan*/ *,struct target_ops*) ; 
 int /*<<< orphan*/  child_clear_solibs () ; 
 scalar_t__ core_bfd ; 
 int /*<<< orphan*/  core_section_load_dll_symbols ; 
 TYPE_1__* solib_end ; 
 int /*<<< orphan*/  solib_symbols_add (scalar_t__,int,int /*<<< orphan*/ ) ; 

void
child_solib_add (char *filename, int from_tty, struct target_ops *target,
		 int readsyms)
{
  if (!readsyms)
    return;
  if (core_bfd)
    {
      child_clear_solibs ();
      bfd_map_over_sections (core_bfd, &core_section_load_dll_symbols, target);
    }
  else
    {
      if (solib_end && solib_end->name)
	     solib_end->objfile = solib_symbols_add (solib_end->name, from_tty,
						solib_end->load_addr);
    }
}