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
struct section_offsets {scalar_t__* offsets; } ;
struct section_addr_info {int dummy; } ;
struct objfile {int num_sections; struct section_offsets* section_offsets; int /*<<< orphan*/  sect_index_rodata; int /*<<< orphan*/  obfd; int /*<<< orphan*/  sect_index_bss; int /*<<< orphan*/  sect_index_data; int /*<<< orphan*/  sect_index_text; int /*<<< orphan*/  objfile_obstack; } ;
struct TYPE_3__ {int /*<<< orphan*/  index; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 int /*<<< orphan*/  SIZEOF_N_SECTION_OFFSETS (int) ; 
 int bfd_count_sections (int /*<<< orphan*/ ) ; 
 TYPE_1__* bfd_get_section_by_name (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ obstack_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xcoff_symfile_offsets (struct objfile *objfile, struct section_addr_info *addrs)
{
  asection *sect = NULL;
  int i;

  objfile->num_sections = bfd_count_sections (objfile->obfd);
  objfile->section_offsets = (struct section_offsets *)
    obstack_alloc (&objfile->objfile_obstack, 
		   SIZEOF_N_SECTION_OFFSETS (objfile->num_sections));

  /* Initialize the section indexes for future use. */
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

  for (i = 0; i < objfile->num_sections; ++i)
    {
      /* syms_from_objfile kindly subtracts from addr the
	 bfd_section_vma of the .text section.  This strikes me as
	 wrong--whether the offset to be applied to symbol reading is
	 relative to the start address of the section depends on the
	 symbol format.  In any event, this whole "addr" concept is
	 pretty broken (it doesn't handle any section but .text
	 sensibly), so just ignore the addr parameter and use 0.
	 rs6000-nat.c will set the correct section offsets via
	 objfile_relocate.  */
	(objfile->section_offsets)->offsets[i] = 0;
    }
}