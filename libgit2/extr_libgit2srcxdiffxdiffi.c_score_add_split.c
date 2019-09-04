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
struct split_score {int penalty; int effective_indent; } ;
struct split_measurement {int pre_indent; int pre_blank; int indent; int post_blank; int post_indent; scalar_t__ end_of_file; } ;

/* Variables and functions */
 scalar_t__ END_OF_FILE_PENALTY ; 
 int POST_BLANK_WEIGHT ; 
 scalar_t__ RELATIVE_DEDENT_PENALTY ; 
 scalar_t__ RELATIVE_DEDENT_WITH_BLANK_PENALTY ; 
 scalar_t__ RELATIVE_INDENT_PENALTY ; 
 scalar_t__ RELATIVE_INDENT_WITH_BLANK_PENALTY ; 
 scalar_t__ RELATIVE_OUTDENT_PENALTY ; 
 scalar_t__ RELATIVE_OUTDENT_WITH_BLANK_PENALTY ; 
 scalar_t__ START_OF_FILE_PENALTY ; 
 int TOTAL_BLANK_WEIGHT ; 

__attribute__((used)) static void score_add_split(const struct split_measurement *m, struct split_score *s)
{
	/*
	 * A place to accumulate penalty factors (positive makes this index more
	 * favored):
	 */
	int post_blank, total_blank, indent, any_blanks;

	if (m->pre_indent == -1 && m->pre_blank == 0)
		s->penalty += START_OF_FILE_PENALTY;

	if (m->end_of_file)
		s->penalty += END_OF_FILE_PENALTY;

	/*
	 * Set post_blank to the number of blank lines following the split,
	 * including the line immediately after the split:
	 */
	post_blank = (m->indent == -1) ? 1 + m->post_blank : 0;
	total_blank = m->pre_blank + post_blank;

	/* Penalties based on nearby blank lines: */
	s->penalty += TOTAL_BLANK_WEIGHT * total_blank;
	s->penalty += POST_BLANK_WEIGHT * post_blank;

	if (m->indent != -1)
		indent = m->indent;
	else
		indent = m->post_indent;

	any_blanks = (total_blank != 0);

	/* Note that the effective indent is -1 at the end of the file: */
	s->effective_indent += indent;

	if (indent == -1) {
		/* No additional adjustments needed. */
	} else if (m->pre_indent == -1) {
		/* No additional adjustments needed. */
	} else if (indent > m->pre_indent) {
		/*
		 * The line is indented more than its predecessor.
		 */
		s->penalty += any_blanks ?
			RELATIVE_INDENT_WITH_BLANK_PENALTY :
			RELATIVE_INDENT_PENALTY;
	} else if (indent == m->pre_indent) {
		/*
		 * The line has the same indentation level as its predecessor.
		 * No additional adjustments needed.
		 */
	} else {
		/*
		 * The line is indented less than its predecessor. It could be
		 * the block terminator of the previous block, but it could
		 * also be the start of a new block (e.g., an "else" block, or
		 * maybe the previous block didn't have a block terminator).
		 * Try to distinguish those cases based on what comes next:
		 */
		if (m->post_indent != -1 && m->post_indent > indent) {
			/*
			 * The following line is indented more. So it is likely
			 * that this line is the start of a block.
			 */
			s->penalty += any_blanks ?
				RELATIVE_OUTDENT_WITH_BLANK_PENALTY :
				RELATIVE_OUTDENT_PENALTY;
		} else {
			/*
			 * That was probably the end of a block.
			 */
			s->penalty += any_blanks ?
				RELATIVE_DEDENT_WITH_BLANK_PENALTY :
				RELATIVE_DEDENT_PENALTY;
		}
	}
}