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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  RESET_HP_UX_GLOBALS () ; 
 int /*<<< orphan*/  SOLIB_RESTART () ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  free_all_objfiles () ; 
 scalar_t__ have_full_symbols () ; 
 scalar_t__ have_partial_symbols () ; 
 int /*<<< orphan*/  printf_unfiltered (char*) ; 
 int /*<<< orphan*/  query (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* symfile_objfile ; 

void
symbol_file_clear (int from_tty)
{
  if ((have_full_symbols () || have_partial_symbols ())
      && from_tty
      && !query ("Discard symbol table from `%s'? ",
		 symfile_objfile->name))
    error ("Not confirmed.");
    free_all_objfiles ();

    /* solib descriptors may have handles to objfiles.  Since their
       storage has just been released, we'd better wipe the solib
       descriptors as well.
     */
#if defined(SOLIB_RESTART)
    SOLIB_RESTART ();
#endif

    symfile_objfile = NULL;
    if (from_tty)
      printf_unfiltered ("No symbol file now.\n");
#ifdef HPUXHPPA
    RESET_HP_UX_GLOBALS ();
#endif
}