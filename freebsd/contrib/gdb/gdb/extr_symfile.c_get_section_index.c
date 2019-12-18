#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct objfile {int /*<<< orphan*/  obfd; } ;
struct TYPE_3__ {int index; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 TYPE_1__* bfd_get_section_by_name (int /*<<< orphan*/ ,char*) ; 

int
get_section_index (struct objfile *objfile, char *section_name)
{
  asection *sect = bfd_get_section_by_name (objfile->obfd, section_name);
  if (sect)
    return sect->index;
  else
    return -1;
}