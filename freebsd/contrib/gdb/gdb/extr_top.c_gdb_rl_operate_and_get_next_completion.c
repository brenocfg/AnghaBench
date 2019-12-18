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
 int /*<<< orphan*/ * after_char_processing_hook ; 
 int operate_saved_history ; 
 int /*<<< orphan*/  rl_get_previous_history (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rl_pre_input_hook ; 
 int /*<<< orphan*/  rl_redisplay () ; 
 int where_history () ; 

__attribute__((used)) static void
gdb_rl_operate_and_get_next_completion (void)
{
  int delta = where_history () - operate_saved_history;
  /* The `key' argument to rl_get_previous_history is ignored.  */
  rl_get_previous_history (delta, 0);
  operate_saved_history = -1;

  /* readline doesn't automatically update the display for us.  */
  rl_redisplay ();

  after_char_processing_hook = NULL;
  rl_pre_input_hook = NULL;
}