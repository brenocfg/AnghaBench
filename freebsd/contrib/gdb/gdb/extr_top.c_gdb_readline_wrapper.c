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
typedef  int /*<<< orphan*/  Function ;

/* Variables and functions */
 int /*<<< orphan*/ * after_char_processing_hook ; 
 scalar_t__ event_loop_p ; 
 char* readline (char*) ; 
 int /*<<< orphan*/ * rl_pre_input_hook ; 

char *
gdb_readline_wrapper (char *prompt)
{
  /* Set the hook that works in this case.  */
  if (event_loop_p && after_char_processing_hook)
    {
      rl_pre_input_hook = (Function *) after_char_processing_hook;
      after_char_processing_hook = NULL;
    }

  return readline (prompt);
}