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
 int /*<<< orphan*/  add_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_set_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_setshow_boolean_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_show_from_set (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_maintenance ; 
 int /*<<< orphan*/  class_obscure ; 
 int /*<<< orphan*/  class_support ; 
 int /*<<< orphan*/  dcache_init () ; 
 int /*<<< orphan*/  do_monitor_command ; 
 int /*<<< orphan*/  dummy_target ; 
 int /*<<< orphan*/  init_dummy_target () ; 
 int /*<<< orphan*/  push_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setdebuglist ; 
 int /*<<< orphan*/  setlist ; 
 int /*<<< orphan*/  showdebuglist ; 
 int /*<<< orphan*/  showlist ; 
 int /*<<< orphan*/  targ_desc ; 
 int /*<<< orphan*/  target_dcache ; 
 int /*<<< orphan*/  target_info ; 
 int /*<<< orphan*/  targetdebug ; 
 int /*<<< orphan*/  trust_readonly ; 
 int /*<<< orphan*/  var_zinteger ; 

void
initialize_targets (void)
{
  init_dummy_target ();
  push_target (&dummy_target);

  add_info ("target", target_info, targ_desc);
  add_info ("files", target_info, targ_desc);

  add_show_from_set 
    (add_set_cmd ("target", class_maintenance, var_zinteger,
		  (char *) &targetdebug,
		  "Set target debugging.\n\
When non-zero, target debugging is enabled.", &setdebuglist),
     &showdebuglist);

  add_setshow_boolean_cmd ("trust-readonly-sections", class_support, 
			   &trust_readonly, "\
Set mode for reading from readonly sections.\n\
When this mode is on, memory reads from readonly sections (such as .text)\n\
will be read from the object file instead of from the target.  This will\n\
result in significant performance improvement for remote targets.", "\
Show mode for reading from readonly sections.\n",
			   NULL, NULL,
			   &setlist, &showlist);

  add_com ("monitor", class_obscure, do_monitor_command,
	   "Send a command to the remote monitor (remote targets only).");

  target_dcache = dcache_init ();
}