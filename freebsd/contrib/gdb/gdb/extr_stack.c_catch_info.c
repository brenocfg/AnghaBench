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
struct symtab_and_line {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EX_EVENT_CATCH ; 
 int /*<<< orphan*/  deprecated_selected_frame ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fprintf_filtered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  print_frame_label_vars (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct symtab_and_line* target_enable_exception_callback (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
catch_info (char *ignore, int from_tty)
{
  struct symtab_and_line *sal;

  /* Check for target support for exception handling */
  sal = target_enable_exception_callback (EX_EVENT_CATCH, 1);
  if (sal)
    {
      /* Currently not handling this */
      /* Ideally, here we should interact with the C++ runtime
         system to find the list of active handlers, etc. */
      fprintf_filtered (gdb_stdout, "Info catch not supported with this target/compiler combination.\n");
#if 0
      if (!deprecated_selected_frame)
	error ("No frame selected.");
#endif
    }
  else
    {
      /* Assume g++ compiled code -- old v 4.16 behaviour */
      if (!deprecated_selected_frame)
	error ("No frame selected.");

      print_frame_label_vars (deprecated_selected_frame, 0, gdb_stdout);
    }
}