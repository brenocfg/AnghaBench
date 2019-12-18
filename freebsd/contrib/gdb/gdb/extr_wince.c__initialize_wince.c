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
 struct cmd_list_element* add_set_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_show_from_set (struct cmd_list_element*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  child_ops ; 
 int /*<<< orphan*/  class_support ; 
 int /*<<< orphan*/  debug_events ; 
 int /*<<< orphan*/  debug_exceptions ; 
 int /*<<< orphan*/  debug_exec ; 
 int /*<<< orphan*/  debug_memory ; 
 int /*<<< orphan*/  init_child_ops () ; 
 int /*<<< orphan*/  no_class ; 
 int /*<<< orphan*/  remote_add_host ; 
 scalar_t__ remote_directory ; 
 int /*<<< orphan*/  remote_upload ; 
 int /*<<< orphan*/  set_cmd_cfunc (struct cmd_list_element*,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  set_upload_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setlist ; 
 int /*<<< orphan*/  showlist ; 
 int /*<<< orphan*/  var_boolean ; 
 int /*<<< orphan*/  var_string_noescape ; 
 scalar_t__ xstrdup (scalar_t__) ; 

void
_initialize_wince (void)
{
  struct cmd_list_element *set;
  init_child_ops ();

  add_show_from_set
    (add_set_cmd ((char *) "remotedirectory", no_class,
		  var_string_noescape, (char *) &remote_directory,
		  (char *) "Set directory for remote upload.\n",
		  &setlist),
     &showlist);
  remote_directory = xstrdup (remote_directory);

  set = add_set_cmd ((char *) "remoteupload", no_class,
		     var_string_noescape, (char *) &remote_upload,
	       (char *) "Set how to upload executables to remote device.\n",
		     &setlist);
  add_show_from_set (set, &showlist);
  set_cmd_cfunc (set, set_upload_type);
  set_upload_type (NULL, 0);

  add_show_from_set
    (add_set_cmd ((char *) "debugexec", class_support, var_boolean,
		  (char *) &debug_exec,
	      (char *) "Set whether to display execution in child process.",
		  &setlist),
     &showlist);

  add_show_from_set
    (add_set_cmd ((char *) "remoteaddhost", class_support, var_boolean,
		  (char *) &remote_add_host,
		  (char *) "\
Set whether to add this host to remote stub arguments for\n\
debugging over a network.", &setlist),
     &showlist);

  add_show_from_set
    (add_set_cmd ((char *) "debugevents", class_support, var_boolean,
		  (char *) &debug_events,
	  (char *) "Set whether to display kernel events in child process.",
		  &setlist),
     &showlist);

  add_show_from_set
    (add_set_cmd ((char *) "debugmemory", class_support, var_boolean,
		  (char *) &debug_memory,
	(char *) "Set whether to display memory accesses in child process.",
		  &setlist),
     &showlist);

  add_show_from_set
    (add_set_cmd ((char *) "debugexceptions", class_support, var_boolean,
		  (char *) &debug_exceptions,
      (char *) "Set whether to display kernel exceptions in child process.",
		  &setlist),
     &showlist);

  add_target (&child_ops);
}