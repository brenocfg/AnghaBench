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
struct objfile {int flags; TYPE_1__* separate_debug_objfile; int /*<<< orphan*/  num_sections; int /*<<< orphan*/  section_offsets; } ;
struct TYPE_3__ {struct objfile* separate_debug_objfile_backlink; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int OBJF_READNOW ; 
 int OBJF_REORDERED ; 
 int OBJF_SHARED ; 
 int OBJF_USERLOADED ; 
 char* find_separate_debug_file (struct objfile*) ; 
 int /*<<< orphan*/  free_objfile (TYPE_1__*) ; 
 int /*<<< orphan*/  info_verbose ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* symbol_file_add_with_addrs_or_offsets (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
reread_separate_symbols (struct objfile *objfile)
{
  char *debug_file;
  unsigned long crc32;

  /* Does the updated objfile's debug info live in a
     separate file?  */
  debug_file = find_separate_debug_file (objfile);

  if (objfile->separate_debug_objfile)
    {
      /* There are two cases where we need to get rid of
         the old separated debug info objfile:
         - if the new primary objfile doesn't have
         separated debug info, or
         - if the new primary objfile has separate debug
         info, but it's under a different filename.
 
         If the old and new objfiles both have separate
         debug info, under the same filename, then we're
         okay --- if the separated file's contents have
         changed, we will have caught that when we
         visited it in this function's outermost
         loop.  */
      if (! debug_file
          || strcmp (debug_file, objfile->separate_debug_objfile->name) != 0)
        free_objfile (objfile->separate_debug_objfile);
    }

  /* If the new objfile has separate debug info, and we
     haven't loaded it already, do so now.  */
  if (debug_file
      && ! objfile->separate_debug_objfile)
    {
      /* Use the same section offset table as objfile itself.
         Preserve the flags from objfile that make sense.  */
      objfile->separate_debug_objfile
        = (symbol_file_add_with_addrs_or_offsets
           (debug_file,
            info_verbose, /* from_tty: Don't override the default. */
            0, /* No addr table.  */
            objfile->section_offsets, objfile->num_sections,
            0, /* Not mainline.  See comments about this above.  */
            objfile->flags & (OBJF_REORDERED | OBJF_SHARED | OBJF_READNOW
                              | OBJF_USERLOADED)));
      objfile->separate_debug_objfile->separate_debug_objfile_backlink
        = objfile;
    }
}