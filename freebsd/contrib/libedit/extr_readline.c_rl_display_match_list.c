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
 int /*<<< orphan*/  _rl_completion_append_character_function ; 
 int /*<<< orphan*/  e ; 
 int /*<<< orphan*/  fn_display_match_list (int /*<<< orphan*/ ,char**,size_t,size_t,int /*<<< orphan*/ ) ; 

void
rl_display_match_list(char **matches, int len, int max)
{

	fn_display_match_list(e, matches, (size_t)len, (size_t)max,
		_rl_completion_append_character_function);
}