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
 char* PROMPT (int /*<<< orphan*/ ) ; 
 scalar_t__ event_loop_p ; 
 char* gdb_prompt_string ; 

char *
get_prompt (void)
{
  if (event_loop_p)
    return PROMPT (0);
  else
    return gdb_prompt_string;
}