#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct objfile {int dummy; } ;
struct find_targ_sec_arg {scalar_t__ targ_index; TYPE_1__** bfd_sect; int /*<<< orphan*/ * resultp; struct objfile* objfile; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_4__ {scalar_t__ target_index; int /*<<< orphan*/  index; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 int /*<<< orphan*/  SECT_OFF_DATA (struct objfile*) ; 
 int /*<<< orphan*/  SECT_OFF_TEXT (struct objfile*) ; 
 int SEC_CODE ; 
 int SEC_LOAD ; 
 int bfd_get_section_flags (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
find_targ_sec (bfd *abfd, asection *sect, void *obj)
{
  struct find_targ_sec_arg *args = (struct find_targ_sec_arg *) obj;
  struct objfile *objfile = args->objfile;
  if (sect->target_index == args->targ_index)
    {
      /* This is the section.  Figure out what SECT_OFF_* code it is.  */
      if (bfd_get_section_flags (abfd, sect) & SEC_CODE)
	*args->resultp = SECT_OFF_TEXT (objfile);
      else if (bfd_get_section_flags (abfd, sect) & SEC_LOAD)
	*args->resultp = SECT_OFF_DATA (objfile);
      else
	*args->resultp = sect->index;
      *args->bfd_sect = sect;
    }
}