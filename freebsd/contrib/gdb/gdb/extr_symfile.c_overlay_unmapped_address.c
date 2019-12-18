#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ vma; scalar_t__ lma; } ;
typedef  TYPE_1__ asection ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ overlay_debugging ; 
 scalar_t__ pc_in_mapped_range (scalar_t__,TYPE_1__*) ; 
 scalar_t__ section_is_overlay (TYPE_1__*) ; 

CORE_ADDR
overlay_unmapped_address (CORE_ADDR pc, asection *section)
{
  /* FIXME: need bfd *, so we can use bfd_section_lma methods. */

  if (overlay_debugging)
    if (section && section_is_overlay (section) &&
	pc_in_mapped_range (pc, section))
      return pc + section->lma - section->vma;

  return pc;
}