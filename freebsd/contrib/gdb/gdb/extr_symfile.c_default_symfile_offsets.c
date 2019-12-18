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
struct section_offsets {scalar_t__* offsets; } ;
struct section_addr_info {int num_sections; struct other_sections* other; } ;
struct other_sections {scalar_t__ addr; size_t sectindex; scalar_t__ name; } ;
struct objfile {struct section_offsets* section_offsets; int /*<<< orphan*/  num_sections; int /*<<< orphan*/  objfile_obstack; int /*<<< orphan*/  obfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIZEOF_N_SECTION_OFFSETS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_count_sections (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_objfile_sect_indices (struct objfile*) ; 
 int /*<<< orphan*/  memset (struct section_offsets*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ obstack_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
default_symfile_offsets (struct objfile *objfile,
			 struct section_addr_info *addrs)
{
  int i;

  objfile->num_sections = bfd_count_sections (objfile->obfd);
  objfile->section_offsets = (struct section_offsets *)
    obstack_alloc (&objfile->objfile_obstack, 
		   SIZEOF_N_SECTION_OFFSETS (objfile->num_sections));
  memset (objfile->section_offsets, 0, 
	  SIZEOF_N_SECTION_OFFSETS (objfile->num_sections));

  /* Now calculate offsets for section that were specified by the
     caller. */
  for (i = 0; i < addrs->num_sections && addrs->other[i].name; i++)
    {
      struct other_sections *osp ;

      osp = &addrs->other[i] ;
      if (osp->addr == 0)
  	continue;

      /* Record all sections in offsets */
      /* The section_offsets in the objfile are here filled in using
         the BFD index. */
      (objfile->section_offsets)->offsets[osp->sectindex] = osp->addr;
    }

  /* Remember the bfd indexes for the .text, .data, .bss and
     .rodata sections. */
  init_objfile_sect_indices (objfile);
}