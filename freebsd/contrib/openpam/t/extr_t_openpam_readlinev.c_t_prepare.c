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
 int /*<<< orphan*/  T (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comment ; 
 int /*<<< orphan*/  empty_input ; 
 int /*<<< orphan*/  empty_line ; 
 int /*<<< orphan*/  line_continuation_within_whitespace ; 
 int /*<<< orphan*/  many_words ; 
 int /*<<< orphan*/  one_word ; 
 int /*<<< orphan*/  two_words ; 
 int /*<<< orphan*/  unterminated_empty_line ; 
 int /*<<< orphan*/  unterminated_line ; 
 int /*<<< orphan*/  whitespace ; 
 int /*<<< orphan*/  whitespace_before_comment ; 

__attribute__((used)) static int
t_prepare(int argc, char *argv[])
{

	(void)argc;
	(void)argv;

	T(empty_input);
	T(empty_line);
	T(unterminated_empty_line);
	T(whitespace);
	T(comment);
	T(whitespace_before_comment);
	T(line_continuation_within_whitespace);

	T(one_word);
	T(two_words);
	T(many_words);
	T(unterminated_line);

	return (0);
}