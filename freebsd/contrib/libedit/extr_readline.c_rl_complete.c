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
typedef  int /*<<< orphan*/  rl_compentry_func_t ;
typedef  int /*<<< orphan*/  ct_buffer_t ;

/* Variables and functions */
 int CC_REFRESH ; 
 int /*<<< orphan*/  _rl_completion_append_character_function ; 
 int /*<<< orphan*/  _rl_update_pos () ; 
 int /*<<< orphan*/  ct_decode_string (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * e ; 
 int /*<<< orphan*/  el_insertstr (int /*<<< orphan*/ *,char*) ; 
 int fn_complete (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * h ; 
 int /*<<< orphan*/  rl_attempted_completion_function ; 
 int /*<<< orphan*/  rl_attempted_completion_over ; 
 char const* rl_basic_word_break_characters ; 
 scalar_t__ rl_completion_entry_function ; 
 scalar_t__ rl_completion_query_items ; 
 int /*<<< orphan*/  rl_completion_type ; 
 char* rl_completion_word_break_hook () ; 
 int /*<<< orphan*/  rl_end ; 
 scalar_t__ rl_inhibit_completion ; 
 int /*<<< orphan*/  rl_initialize () ; 
 int /*<<< orphan*/  rl_point ; 
 char* stub1 () ; 

int
rl_complete(int ignore __attribute__((__unused__)), int invoking_key)
{
	static ct_buffer_t wbreak_conv, sprefix_conv;
	const char *breakchars;

	if (h == NULL || e == NULL)
		rl_initialize();

	if (rl_inhibit_completion) {
		char arr[2];
		arr[0] = (char)invoking_key;
		arr[1] = '\0';
		el_insertstr(e, arr);
		return CC_REFRESH;
	}

	if (rl_completion_word_break_hook != NULL)
		breakchars = (*rl_completion_word_break_hook)();
	else
		breakchars = rl_basic_word_break_characters;

	_rl_update_pos();

	/* Just look at how many global variables modify this operation! */
	return fn_complete(e,
	    (rl_compentry_func_t *)rl_completion_entry_function,
	    rl_attempted_completion_function,
	    ct_decode_string(rl_basic_word_break_characters, &wbreak_conv),
	    ct_decode_string(breakchars, &sprefix_conv),
	    _rl_completion_append_character_function,
	    (size_t)rl_completion_query_items,
	    &rl_completion_type, &rl_attempted_completion_over,
	    &rl_point, &rl_end);


}