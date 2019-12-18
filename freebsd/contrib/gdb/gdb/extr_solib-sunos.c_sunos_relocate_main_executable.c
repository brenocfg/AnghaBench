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
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  asection ;
struct TYPE_3__ {int num_sections; int /*<<< orphan*/  section_offsets; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ ANOFFSET (int /*<<< orphan*/ ,int) ; 
 int DYNAMIC ; 
 int bfd_get_file_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bfd_get_section_by_name (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ bfd_get_start_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  exec_bfd ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,struct section_offsets*) ; 
 int /*<<< orphan*/  objfile_relocate (TYPE_1__*,struct section_offsets*) ; 
 scalar_t__ read_pc () ; 
 TYPE_1__* symfile_objfile ; 
 struct section_offsets* xcalloc (int,int) ; 
 int /*<<< orphan*/  xfree ; 

__attribute__((used)) static void
sunos_relocate_main_executable (void)
{
  asection *interp_sect;
  CORE_ADDR pc = read_pc ();

  /* Decide if the objfile needs to be relocated.  As indicated above,
     we will only be here when execution is stopped at the beginning
     of the program.  Relocation is necessary if the address at which
     we are presently stopped differs from the start address stored in
     the executable AND there's no interpreter section.  The condition
     regarding the interpreter section is very important because if
     there *is* an interpreter section, execution will begin there
     instead.  When there is an interpreter section, the start address
     is (presumably) used by the interpreter at some point to start
     execution of the program.

     If there is an interpreter, it is normal for it to be set to an
     arbitrary address at the outset.  The job of finding it is
     handled in enable_break().

     So, to summarize, relocations are necessary when there is no
     interpreter section and the start address obtained from the
     executable is different from the address at which GDB is
     currently stopped.
     
     [ The astute reader will note that we also test to make sure that
       the executable in question has the DYNAMIC flag set.  It is my
       opinion that this test is unnecessary (undesirable even).  It
       was added to avoid inadvertent relocation of an executable
       whose e_type member in the ELF header is not ET_DYN.  There may
       be a time in the future when it is desirable to do relocations
       on other types of files as well in which case this condition
       should either be removed or modified to accomodate the new file
       type.  (E.g, an ET_EXEC executable which has been built to be
       position-independent could safely be relocated by the OS if
       desired.  It is true that this violates the ABI, but the ABI
       has been known to be bent from time to time.)  - Kevin, Nov 2000. ]
     */

  interp_sect = bfd_get_section_by_name (exec_bfd, ".interp");
  if (interp_sect == NULL 
      && (bfd_get_file_flags (exec_bfd) & DYNAMIC) != 0
      && bfd_get_start_address (exec_bfd) != pc)
    {
      struct cleanup *old_chain;
      struct section_offsets *new_offsets;
      int i, changed;
      CORE_ADDR displacement;
      
      /* It is necessary to relocate the objfile.  The amount to
	 relocate by is simply the address at which we are stopped
	 minus the starting address from the executable.

	 We relocate all of the sections by the same amount.  This
	 behavior is mandated by recent editions of the System V ABI. 
	 According to the System V Application Binary Interface,
	 Edition 4.1, page 5-5:

	   ...  Though the system chooses virtual addresses for
	   individual processes, it maintains the segments' relative
	   positions.  Because position-independent code uses relative
	   addressesing between segments, the difference between
	   virtual addresses in memory must match the difference
	   between virtual addresses in the file.  The difference
	   between the virtual address of any segment in memory and
	   the corresponding virtual address in the file is thus a
	   single constant value for any one executable or shared
	   object in a given process.  This difference is the base
	   address.  One use of the base address is to relocate the
	   memory image of the program during dynamic linking.

	 The same language also appears in Edition 4.0 of the System V
	 ABI and is left unspecified in some of the earlier editions.  */

      displacement = pc - bfd_get_start_address (exec_bfd);
      changed = 0;

      new_offsets = xcalloc (symfile_objfile->num_sections,
			     sizeof (struct section_offsets));
      old_chain = make_cleanup (xfree, new_offsets);

      for (i = 0; i < symfile_objfile->num_sections; i++)
	{
	  if (displacement != ANOFFSET (symfile_objfile->section_offsets, i))
	    changed = 1;
	  new_offsets->offsets[i] = displacement;
	}

      if (changed)
	objfile_relocate (symfile_objfile, new_offsets);

      do_cleanups (old_chain);
    }
}