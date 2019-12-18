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
 int /*<<< orphan*/  add_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 struct cmd_list_element* add_com (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_com_alias (char*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  add_info (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_info_alias (char*,char*,int) ; 
 int /*<<< orphan*/  add_prefix_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_set_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_show_from_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  child_ops ; 
 int /*<<< orphan*/  class_alias ; 
 int /*<<< orphan*/  class_files ; 
 int /*<<< orphan*/  class_info ; 
 int /*<<< orphan*/  class_support ; 
 int /*<<< orphan*/  debug_events ; 
 int /*<<< orphan*/  debug_exceptions ; 
 int /*<<< orphan*/  debug_exec ; 
 int /*<<< orphan*/  debug_memory ; 
 int /*<<< orphan*/  display_selectors ; 
 int /*<<< orphan*/  dll_symbol_command ; 
 int /*<<< orphan*/  filename_completer ; 
 int /*<<< orphan*/  info_dll_command ; 
 int /*<<< orphan*/  info_w32_cmdlist ; 
 int /*<<< orphan*/  info_w32_command ; 
 int /*<<< orphan*/  infolist ; 
 int /*<<< orphan*/  init_child_ops () ; 
 int /*<<< orphan*/  new_console ; 
 int /*<<< orphan*/  new_group ; 
 int /*<<< orphan*/  set_cmd_completer (struct cmd_list_element*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setlist ; 
 int /*<<< orphan*/  showlist ; 
 int /*<<< orphan*/  useshell ; 
 int /*<<< orphan*/  var_boolean ; 

void
_initialize_win32_nat (void)
{
  struct cmd_list_element *c;

  init_child_ops ();

  c = add_com ("dll-symbols", class_files, dll_symbol_command,
	       "Load dll library symbols from FILE.");
  set_cmd_completer (c, filename_completer);

  add_com_alias ("sharedlibrary", "dll-symbols", class_alias, 1);

  add_show_from_set (add_set_cmd ("shell", class_support, var_boolean,
				  (char *) &useshell,
		 "Set use of shell to start subprocess.",
				  &setlist),
		     &showlist);

  add_show_from_set (add_set_cmd ("new-console", class_support, var_boolean,
				  (char *) &new_console,
		 "Set creation of new console when creating child process.",
				  &setlist),
		     &showlist);

  add_show_from_set (add_set_cmd ("new-group", class_support, var_boolean,
				  (char *) &new_group,
		   "Set creation of new group when creating child process.",
				  &setlist),
		     &showlist);

  add_show_from_set (add_set_cmd ("debugexec", class_support, var_boolean,
				  (char *) &debug_exec,
		       "Set whether to display execution in child process.",
				  &setlist),
		     &showlist);

  add_show_from_set (add_set_cmd ("debugevents", class_support, var_boolean,
				  (char *) &debug_events,
		   "Set whether to display kernel events in child process.",
				  &setlist),
		     &showlist);

  add_show_from_set (add_set_cmd ("debugmemory", class_support, var_boolean,
				  (char *) &debug_memory,
		 "Set whether to display memory accesses in child process.",
				  &setlist),
		     &showlist);

  add_show_from_set (add_set_cmd ("debugexceptions", class_support, var_boolean,
				  (char *) &debug_exceptions,
	       "Set whether to display kernel exceptions in child process.",
				  &setlist),
		     &showlist);

  add_info ("dll", info_dll_command, "Status of loaded DLLs.");
  add_info_alias ("sharedlibrary", "dll", 1);

  add_prefix_cmd ("w32", class_info, info_w32_command,
		  "Print information specific to Win32 debugging.",
		  &info_w32_cmdlist, "info w32 ", 0, &infolist);

  add_cmd ("selector", class_info, display_selectors,
	   "Display selectors infos.",
	   &info_w32_cmdlist);

  add_target (&child_ops);
}