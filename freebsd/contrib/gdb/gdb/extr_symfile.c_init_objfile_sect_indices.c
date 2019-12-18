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
struct objfile {int sect_index_text; int sect_index_data; int sect_index_bss; int sect_index_rodata; int num_sections; int /*<<< orphan*/  section_offsets; int /*<<< orphan*/  obfd; } ;
struct TYPE_3__ {int index; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 scalar_t__ ANOFFSET (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* bfd_get_section_by_name (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
init_objfile_sect_indices (struct objfile *objfile)
{
  asection *sect;
  int i;
  
  sect = bfd_get_section_by_name (objfile->obfd, ".text");
  if (sect) 
    objfile->sect_index_text = sect->index;

  sect = bfd_get_section_by_name (objfile->obfd, ".data");
  if (sect) 
    objfile->sect_index_data = sect->index;

  sect = bfd_get_section_by_name (objfile->obfd, ".bss");
  if (sect) 
    objfile->sect_index_bss = sect->index;

  sect = bfd_get_section_by_name (objfile->obfd, ".rodata");
  if (sect) 
    objfile->sect_index_rodata = sect->index;

  /* This is where things get really weird...  We MUST have valid
     indices for the various sect_index_* members or gdb will abort.
     So if for example, there is no ".text" section, we have to
     accomodate that.  Except when explicitly adding symbol files at
     some address, section_offsets contains nothing but zeros, so it
     doesn't matter which slot in section_offsets the individual
     sect_index_* members index into.  So if they are all zero, it is
     safe to just point all the currently uninitialized indices to the
     first slot. */

  for (i = 0; i < objfile->num_sections; i++)
    {
      if (ANOFFSET (objfile->section_offsets, i) != 0)
	{
	  break;
	}
    }
  if (i == objfile->num_sections)
    {
      if (objfile->sect_index_text == -1)
	objfile->sect_index_text = 0;
      if (objfile->sect_index_data == -1)
	objfile->sect_index_data = 0;
      if (objfile->sect_index_bss == -1)
	objfile->sect_index_bss = 0;
      if (objfile->sect_index_rodata == -1)
	objfile->sect_index_rodata = 0;
    }
}