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
 scalar_t__ bfd_get_section_size (TYPE_1__*) ; 

__attribute__((used)) static int
sections_overlap (asection *a, asection *b)
{
  /* FIXME: need bfd *, so we can use bfd_section_vma methods. */

  CORE_ADDR a_start = a->vma;
  CORE_ADDR a_end = a->vma + bfd_get_section_size (a);
  CORE_ADDR b_start = b->vma;
  CORE_ADDR b_end = b->vma + bfd_get_section_size (b);

  return (a_start < b_end && b_start < a_end);
}