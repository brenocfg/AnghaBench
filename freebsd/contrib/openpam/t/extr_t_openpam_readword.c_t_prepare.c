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
 int /*<<< orphan*/  comment_after_word ; 
 int /*<<< orphan*/  comment_at_eof ; 
 int /*<<< orphan*/  double_quote_after_word ; 
 int /*<<< orphan*/  double_quote_before_word ; 
 int /*<<< orphan*/  double_quote_within_word ; 
 int /*<<< orphan*/  double_quoted_comment ; 
 int /*<<< orphan*/  double_quoted_whitespace ; 
 int /*<<< orphan*/  double_quoted_words ; 
 int /*<<< orphan*/  double_quotes_within_single_quotes ; 
 int /*<<< orphan*/  double_whitespace_after_word ; 
 int /*<<< orphan*/  double_whitespace_before_word ; 
 int /*<<< orphan*/  empty_double_quotes ; 
 int /*<<< orphan*/  empty_input ; 
 int /*<<< orphan*/  empty_line ; 
 int /*<<< orphan*/  empty_single_quotes ; 
 int /*<<< orphan*/  escape_at_eof ; 
 int /*<<< orphan*/  escaped_comment ; 
 int /*<<< orphan*/  escaped_double_quote ; 
 int /*<<< orphan*/  escaped_double_quote_within_double_quotes ; 
 int /*<<< orphan*/  escaped_double_quote_within_single_quotes ; 
 int /*<<< orphan*/  escaped_escape ; 
 int /*<<< orphan*/  escaped_escape_within_double_quotes ; 
 int /*<<< orphan*/  escaped_escape_within_single_quotes ; 
 int /*<<< orphan*/  escaped_letter ; 
 int /*<<< orphan*/  escaped_letter_within_double_quotes ; 
 int /*<<< orphan*/  escaped_letter_within_single_quotes ; 
 int /*<<< orphan*/  escaped_newline_after_word ; 
 int /*<<< orphan*/  escaped_newline_before_word ; 
 int /*<<< orphan*/  escaped_newline_within_word ; 
 int /*<<< orphan*/  escaped_single_quote ; 
 int /*<<< orphan*/  escaped_single_quote_within_double_quotes ; 
 int /*<<< orphan*/  escaped_single_quote_within_single_quotes ; 
 int /*<<< orphan*/  escaped_whitespace ; 
 int /*<<< orphan*/  escaped_whitespace_within_double_quotes ; 
 int /*<<< orphan*/  escaped_whitespace_within_single_quotes ; 
 int /*<<< orphan*/  line_continuation_after_whitespace ; 
 int /*<<< orphan*/  line_continuation_before_whitespace ; 
 int /*<<< orphan*/  line_continuation_within_whitespace ; 
 int /*<<< orphan*/  line_continuation_within_word ; 
 int /*<<< orphan*/  multiple_whitespace ; 
 int /*<<< orphan*/  naked_double_quote ; 
 int /*<<< orphan*/  naked_escape ; 
 int /*<<< orphan*/  naked_single_quote ; 
 int /*<<< orphan*/  single_quote_after_word ; 
 int /*<<< orphan*/  single_quote_before_word ; 
 int /*<<< orphan*/  single_quote_within_word ; 
 int /*<<< orphan*/  single_quoted_comment ; 
 int /*<<< orphan*/  single_quoted_whitespace ; 
 int /*<<< orphan*/  single_quoted_words ; 
 int /*<<< orphan*/  single_quotes_within_double_quotes ; 
 int /*<<< orphan*/  single_whitespace ; 
 int /*<<< orphan*/  single_whitespace_after_word ; 
 int /*<<< orphan*/  single_whitespace_before_word ; 
 int /*<<< orphan*/  single_word ; 
 int /*<<< orphan*/  two_words ; 
 int /*<<< orphan*/  unterminated_line ; 
 int /*<<< orphan*/  whitespace_before_comment ; 
 int /*<<< orphan*/  word_containing_hash ; 

__attribute__((used)) static int
t_prepare(int argc, char *argv[])
{

	(void)argc;
	(void)argv;

	T(empty_input);
	T(empty_line);
	T(unterminated_line);
	T(single_whitespace);
	T(multiple_whitespace);
	T(comment);
	T(whitespace_before_comment);
	T(single_quoted_comment);
	T(double_quoted_comment);
	T(comment_at_eof);

	T(single_word);
	T(single_whitespace_before_word);
	T(double_whitespace_before_word);
	T(single_whitespace_after_word);
	T(double_whitespace_after_word);
	T(comment_after_word);
	T(word_containing_hash);
	T(two_words);

	T(naked_escape);
	T(escaped_escape);
	T(escaped_whitespace);
	T(escaped_newline_before_word);
	T(escaped_newline_within_word);
	T(escaped_newline_after_word);
	T(escaped_letter);
	T(escaped_comment);
	T(escape_at_eof);

	T(naked_single_quote);
	T(naked_double_quote);
	T(empty_single_quotes);
	T(empty_double_quotes);
	T(single_quotes_within_double_quotes);
	T(double_quotes_within_single_quotes);
	T(single_quoted_whitespace);
	T(double_quoted_whitespace);
	T(single_quoted_words);
	T(double_quoted_words);

	T(single_quote_before_word);
	T(double_quote_before_word);
	T(single_quote_within_word);
	T(double_quote_within_word);
	T(single_quote_after_word);
	T(double_quote_after_word);

	T(escaped_single_quote);
	T(escaped_double_quote);
	T(escaped_whitespace_within_single_quotes);
	T(escaped_whitespace_within_double_quotes);
	T(escaped_letter_within_single_quotes);
	T(escaped_letter_within_double_quotes);
	T(escaped_escape_within_single_quotes);
	T(escaped_escape_within_double_quotes);
	T(escaped_single_quote_within_single_quotes);
	T(escaped_double_quote_within_single_quotes);
	T(escaped_single_quote_within_double_quotes);
	T(escaped_double_quote_within_double_quotes);

	T(line_continuation_within_whitespace);
	T(line_continuation_before_whitespace);
	T(line_continuation_after_whitespace);
	T(line_continuation_within_word);

	return (0);
}