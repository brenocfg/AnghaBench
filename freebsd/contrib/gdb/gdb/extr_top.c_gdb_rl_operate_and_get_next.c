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
 scalar_t__ after_char_processing_hook ; 
 scalar_t__ event_loop_p ; 
 scalar_t__ gdb_rl_operate_and_get_next_completion ; 
 scalar_t__ history_is_stifled () ; 
 int history_length ; 
 int max_input_history ; 
 int operate_saved_history ; 
 int rl_newline (int,int) ; 
 int /*<<< orphan*/ * rl_pre_input_hook ; 
 int where_history () ; 

__attribute__((used)) static int
gdb_rl_operate_and_get_next (int count, int key)
{
  int where;

  if (event_loop_p)
    {
      /* Use the async hook.  */
      after_char_processing_hook = gdb_rl_operate_and_get_next_completion;
    }
  else
    {
      /* This hook only works correctly when we are using the
	 synchronous readline.  */
      rl_pre_input_hook = (Function *) gdb_rl_operate_and_get_next_completion;
    }

  /* Find the current line, and find the next line to use.  */
  where = where_history();

  /* FIXME: kettenis/20020817: max_input_history is renamed into
     history_max_entries in readline-4.2.  When we do a new readline
     import, we should probably change it here too, even though
     readline maintains backwards compatibility for now by still
     defining max_input_history.  */
  if ((history_is_stifled () && (history_length >= max_input_history)) ||
      (where >= history_length - 1))
    operate_saved_history = where;
  else
    operate_saved_history = where + 1;

  return rl_newline (1, key);
}