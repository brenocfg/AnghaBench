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

/* Variables and functions */
 int /*<<< orphan*/  add_com (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_info (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_set_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_show_from_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  auto_solib_add ; 
 int auto_solib_limit ; 
 int /*<<< orphan*/  class_files ; 
 int /*<<< orphan*/  class_support ; 
 int /*<<< orphan*/  setlist ; 
 int /*<<< orphan*/  showlist ; 
 int /*<<< orphan*/  som_sharedlibrary_info_command ; 
 int /*<<< orphan*/  som_solib_restart () ; 
 int /*<<< orphan*/  som_solib_sharedlibrary_command ; 
 int /*<<< orphan*/  var_boolean ; 
 int /*<<< orphan*/  var_zinteger ; 

void
_initialize_som_solib (void)
{
  add_com ("sharedlibrary", class_files, som_solib_sharedlibrary_command,
	   "Load shared object library symbols for files matching REGEXP.");
  add_info ("sharedlibrary", som_sharedlibrary_info_command,
	    "Status of loaded shared object libraries.");

  add_show_from_set
    (add_set_cmd ("auto-solib-add", class_support, var_boolean,
		  (char *) &auto_solib_add,
		  "Set autoloading of shared library symbols.\n\
If \"on\", symbols from all shared object libraries will be loaded\n\
automatically when the inferior begins execution, when the dynamic linker\n\
informs gdb that a new library has been loaded, or when attaching to the\n\
inferior.  Otherwise, symbols must be loaded manually, using `sharedlibrary'.",
		  &setlist),
     &showlist);

  add_show_from_set
    (add_set_cmd ("auto-solib-limit", class_support, var_zinteger,
		  (char *) &auto_solib_limit,
		  "Set threshold (in Mb) for autoloading shared library symbols.\n\
When shared library autoloading is enabled, new libraries will be loaded\n\
only until the total size of shared library symbols exceeds this\n\
threshold in megabytes.  Is ignored when using `sharedlibrary'.",
		  &setlist),
     &showlist);

  /* ??rehrauer: On HP-UX, the kernel parameter MAXDSIZ limits how
     much data space a process can use.  We ought to be reading
     MAXDSIZ and setting auto_solib_limit to some large fraction of
     that value.  If not that, we maybe ought to be setting it smaller
     than the default for MAXDSIZ (that being 64Mb, I believe).
     However, [1] this threshold is only crudely approximated rather
     than actually measured, and [2] 50 Mbytes is too small for
     debugging gdb itself.  Thus, the arbitrary 100 figure.  */
  auto_solib_limit = 100;	/* Megabytes */

  som_solib_restart ();
}