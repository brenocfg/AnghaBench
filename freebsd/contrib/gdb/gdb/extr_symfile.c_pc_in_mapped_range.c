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
struct TYPE_5__ {scalar_t__ vma; } ;
typedef  TYPE_1__ asection ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int bfd_get_section_size (TYPE_1__*) ; 
 scalar_t__ overlay_debugging ; 
 scalar_t__ section_is_overlay (TYPE_1__*) ; 

CORE_ADDR
pc_in_mapped_range (CORE_ADDR pc, asection *section)
{
  /* FIXME: need bfd *, so we can use bfd_section_vma methods. */

  int size;

  if (overlay_debugging)
    if (section && section_is_overlay (section))
      {
	size = bfd_get_section_size (section);
	if (section->vma <= pc && pc < section->vma + size)
	  return 1;
      }
  return 0;
}