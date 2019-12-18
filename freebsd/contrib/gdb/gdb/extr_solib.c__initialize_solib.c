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
struct cmd_list_element {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_com (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_info (char*,int /*<<< orphan*/ ,char*) ; 
 struct cmd_list_element* add_set_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_show_from_set (struct cmd_list_element*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  auto_solib_add ; 
 int /*<<< orphan*/  class_files ; 
 int /*<<< orphan*/  class_support ; 
 int /*<<< orphan*/  filename_completer ; 
 int /*<<< orphan*/  gdb_sysroot ; 
 int /*<<< orphan*/  info_sharedlibrary_command ; 
 int /*<<< orphan*/  no_shared_libraries ; 
 int /*<<< orphan*/  reload_shared_libraries ; 
 int /*<<< orphan*/  set_cmd_cfunc (struct cmd_list_element*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cmd_completer (struct cmd_list_element*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setlist ; 
 int /*<<< orphan*/  sharedlibrary_command ; 
 int /*<<< orphan*/  showlist ; 
 scalar_t__ solib_absolute_prefix ; 
 int /*<<< orphan*/  solib_search_path ; 
 int /*<<< orphan*/  var_boolean ; 
 int /*<<< orphan*/  var_filename ; 
 int /*<<< orphan*/  var_string ; 
 scalar_t__ xstrdup (int /*<<< orphan*/ ) ; 

void
_initialize_solib (void)
{
  struct cmd_list_element *c;

  add_com ("sharedlibrary", class_files, sharedlibrary_command,
	   "Load shared object library symbols for files matching REGEXP.");
  add_info ("sharedlibrary", info_sharedlibrary_command,
	    "Status of loaded shared object libraries.");
  add_com ("nosharedlibrary", class_files, no_shared_libraries,
	   "Unload all shared object library symbols.");

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

  c = add_set_cmd ("solib-absolute-prefix", class_support, var_filename,
		   (char *) &solib_absolute_prefix,
		   "Set prefix for loading absolute shared library symbol files.\n\
For other (relative) files, you can add values using `set solib-search-path'.",
		   &setlist);
  add_show_from_set (c, &showlist);
  set_cmd_cfunc (c, reload_shared_libraries);
  set_cmd_completer (c, filename_completer);

  /* Set the default value of "solib-absolute-prefix" from the sysroot, if
     one is set.  */
  solib_absolute_prefix = xstrdup (gdb_sysroot);

  c = add_set_cmd ("solib-search-path", class_support, var_string,
		   (char *) &solib_search_path,
		   "Set the search path for loading non-absolute shared library symbol files.\n\
This takes precedence over the environment variables PATH and LD_LIBRARY_PATH.",
		   &setlist);
  add_show_from_set (c, &showlist);
  set_cmd_cfunc (c, reload_shared_libraries);
  set_cmd_completer (c, filename_completer);
}