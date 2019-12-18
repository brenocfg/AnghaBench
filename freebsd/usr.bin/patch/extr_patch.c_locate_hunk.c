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
typedef  int LINENUM ;

/* Variables and functions */
 scalar_t__ CONTEXT_DIFF ; 
 scalar_t__ NEW_CONTEXT_DIFF ; 
 scalar_t__ UNI_DIFF ; 
 int debug ; 
 scalar_t__ diff_type ; 
 int input_lines ; 
 int last_frozen_line ; 
 int last_offset ; 
 scalar_t__ patch_match (int,int,int) ; 
 int pch_context () ; 
 int pch_first () ; 
 int pch_ptrn_lines () ; 
 int /*<<< orphan*/  say (char*,...) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static LINENUM
locate_hunk(LINENUM fuzz)
{
	LINENUM	first_guess = pch_first() + last_offset;
	LINENUM	offset;
	LINENUM	pat_lines = pch_ptrn_lines();
	LINENUM	max_pos_offset = input_lines - first_guess - pat_lines + 1;
	LINENUM	max_neg_offset = first_guess - last_frozen_line - 1 + pch_context();

	if (pat_lines == 0) {		/* null range matches always */
		if (verbose && fuzz == 0 && (diff_type == CONTEXT_DIFF
		    || diff_type == NEW_CONTEXT_DIFF
		    || diff_type == UNI_DIFF)) {
			say("Empty context always matches.\n");
		}
		return (first_guess);
	}
	if (max_neg_offset >= first_guess)	/* do not try lines < 0 */
		max_neg_offset = first_guess - 1;
	if (first_guess <= input_lines && patch_match(first_guess, 0, fuzz))
		return first_guess;
	for (offset = 1; ; offset++) {
		bool	check_after = (offset <= max_pos_offset);
		bool	check_before = (offset <= max_neg_offset);

		if (check_after && patch_match(first_guess, offset, fuzz)) {
#ifdef DEBUGGING
			if (debug & 1)
				say("Offset changing from %ld to %ld\n",
				    last_offset, offset);
#endif
			last_offset = offset;
			return first_guess + offset;
		} else if (check_before && patch_match(first_guess, -offset, fuzz)) {
#ifdef DEBUGGING
			if (debug & 1)
				say("Offset changing from %ld to %ld\n",
				    last_offset, -offset);
#endif
			last_offset = -offset;
			return first_guess - offset;
		} else if (!check_before && !check_after)
			return 0;
	}
}