#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void (* to_rcmd ) (char*,struct ui_file*) ;} ;
struct TYPE_3__ {void (* to_rcmd ) (char*,struct ui_file*) ;} ;

/* Variables and functions */
 TYPE_2__ current_target ; 
 TYPE_1__ debug_target ; 
 void debug_to_rcmd (char*,struct ui_file*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  gdb_stdtarg ; 
 int /*<<< orphan*/  target_rcmd (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ tcomplain ; 

__attribute__((used)) static void
do_monitor_command (char *cmd,
		 int from_tty)
{
  if ((current_target.to_rcmd
       == (void (*) (char *, struct ui_file *)) tcomplain)
      || (current_target.to_rcmd == debug_to_rcmd
	  && (debug_target.to_rcmd
	      == (void (*) (char *, struct ui_file *)) tcomplain)))
    {
      error ("\"monitor\" command not supported by this target.\n");
    }
  target_rcmd (cmd, gdb_stdtarg);
}