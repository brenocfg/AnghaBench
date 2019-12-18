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
 int /*<<< orphan*/  rl_prompt ; 
 int /*<<< orphan*/  tui_rl_saved_prompt ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xstrdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tui_prep_terminal (int notused1)
{
  /* Save the prompt registered in readline to correctly display it.
     (we can't use gdb_prompt() due to secondary prompts and can't use
     rl_prompt because it points to an alloca buffer).  */
  xfree (tui_rl_saved_prompt);
  tui_rl_saved_prompt = xstrdup (rl_prompt);
}