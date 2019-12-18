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
struct section_offsets {int /*<<< orphan*/ * offsets; } ;
struct section_addr_info {TYPE_1__* other; } ;
struct objfile {int num_sections; int sect_index_data; int sect_index_bss; int sect_index_rodata; struct section_offsets* section_offsets; scalar_t__ sect_index_text; int /*<<< orphan*/  objfile_obstack; int /*<<< orphan*/  obfd; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; scalar_t__ name; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  SIZEOF_N_SECTION_OFFSETS (int) ; 
 int bfd_count_sections (int /*<<< orphan*/ ) ; 
 scalar_t__ obstack_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  som_solib_section_offsets (struct objfile*,struct section_offsets*) ; 
 scalar_t__ strcmp (scalar_t__,char*) ; 

__attribute__((used)) static void
som_symfile_offsets (struct objfile *objfile, struct section_addr_info *addrs)
{
  int i;
  CORE_ADDR text_addr;

  objfile->num_sections = bfd_count_sections (objfile->obfd);
  objfile->section_offsets = (struct section_offsets *)
    obstack_alloc (&objfile->objfile_obstack, 
		   SIZEOF_N_SECTION_OFFSETS (objfile->num_sections));

  /* FIXME: ezannoni 2000-04-20 The section names in SOM are not
     .text, .data, etc, but $TEXT$, $DATA$,... We should initialize
     SET_OFF_* from bfd. (See default_symfile_offsets()). But I don't
     know the correspondence between SOM sections and GDB's idea of
     section names. So for now we default to what is was before these
     changes.*/
  objfile->sect_index_text = 0;
  objfile->sect_index_data = 1;
  objfile->sect_index_bss = 2;
  objfile->sect_index_rodata = 3;

  /* First see if we're a shared library.  If so, get the section
     offsets from the library, else get them from addrs.  */
  if (!som_solib_section_offsets (objfile, objfile->section_offsets))
    {
      /* Note: Here is OK to compare with ".text" because this is the
         name that gdb itself gives to that section, not the SOM
         name. */
      for (i = 0; i < objfile->num_sections && addrs->other[i].name; i++)
	if (strcmp (addrs->other[i].name, ".text") == 0)
	  break;
      text_addr = addrs->other[i].addr;

      for (i = 0; i < objfile->num_sections; i++)
	(objfile->section_offsets)->offsets[i] = text_addr;
    }
}