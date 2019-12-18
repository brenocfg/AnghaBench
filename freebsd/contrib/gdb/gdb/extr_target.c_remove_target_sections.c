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
struct target_ops {struct section_table* to_sections_end; struct section_table* to_sections; } ;
struct section_table {int /*<<< orphan*/ * bfd; } ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  target_resize_to_sections (struct target_ops*,int) ; 
 int target_struct_size ; 
 struct target_ops** target_structs ; 

void
remove_target_sections (bfd *abfd)
{
  struct target_ops **t;

  for (t = target_structs; t < target_structs + target_struct_size; t++)
    {
      struct section_table *src, *dest;

      dest = (*t)->to_sections;
      for (src = (*t)->to_sections; src < (*t)->to_sections_end; src++)
	if (src->bfd != abfd)
	  {
	    /* Keep this section.  */
	    if (dest < src) *dest = *src;
	    dest++;
	  }

      /* If we've dropped any sections, resize the section table.  */
      if (dest < src)
	target_resize_to_sections (*t, dest - src);
    }
}