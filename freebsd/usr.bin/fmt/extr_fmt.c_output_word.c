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
typedef  char wchar_t ;

/* Variables and functions */
 scalar_t__ coalesce_spaces_P ; 
 size_t goal_length ; 
 size_t max_length ; 
 char const* output_buffer ; 
 size_t output_buffer_length ; 
 int output_in_paragraph ; 
 int /*<<< orphan*/  output_indent (size_t) ; 
 size_t pending_spaces ; 
 int /*<<< orphan*/  putwchar (char) ; 
 int /*<<< orphan*/  sentence_enders ; 
 scalar_t__ wcschr (int /*<<< orphan*/ ,char const) ; 
 int wcwidth (char const) ; 
 int /*<<< orphan*/  wmemcpy (char const*,char const*,size_t) ; 
 int /*<<< orphan*/  wmemset (char const*,int,size_t) ; 
 int /*<<< orphan*/  wprintf (char*,int,char const*) ; 
 size_t x ; 
 size_t x0 ; 

__attribute__((used)) static void
output_word(size_t indent0, size_t indent1, const wchar_t *word, size_t length, size_t spaces)
{
	size_t new_x;
	size_t indent = output_in_paragraph ? indent1 : indent0;
	size_t width;
	const wchar_t *p;
	int cwidth;

	for (p = word, width = 0; p < &word[length]; p++)
		width += (cwidth = wcwidth(*p)) > 0 ? cwidth : 1;

	new_x = x + pending_spaces + width;

	/*
	 * If either |spaces==0| (at end of line) or |coalesce_spaces_P|
	 * (squashing internal whitespace), then add just one space; except
	 * that if the last character was a sentence-ender we actually add
	 * two spaces.
	 */
	if (coalesce_spaces_P || spaces == 0)
		spaces = wcschr(sentence_enders, word[length - 1]) ? 2 : 1;

	if (new_x <= goal_length) {
		/*
		 * After adding the word we still aren't at the goal length,
		 * so clearly we add it to the buffer rather than outputing
		 * it.
		 */
		wmemset(output_buffer + output_buffer_length, L' ',
		    pending_spaces);
		x0 += pending_spaces;
		x += pending_spaces;
		output_buffer_length += pending_spaces;
		wmemcpy(output_buffer + output_buffer_length, word, length);
		x0 += width;
		x += width;
		output_buffer_length += length;
		pending_spaces = spaces;
	} else {
		/*
		 * Adding the word takes us past the goal. Print the
		 * line-so-far, and the word too iff either (1) the lsf is
		 * empty or (2) that makes us nearer the goal but doesn't
		 * take us over the limit, or (3) the word on its own takes
		 * us over the limit. In case (3) we put a newline in
		 * between.
		 */
		if (indent > 0)
			output_indent(indent);
		wprintf(L"%.*ls", (int)output_buffer_length, output_buffer);
		if (x0 == 0 || (new_x <= max_length &&
		    new_x - goal_length <= goal_length - x)) {
			wprintf(L"%*ls", (int)pending_spaces, L"");
			goto write_out_word;
		} else {
			/*
			 * If the word takes us over the limit on its own,
			 * just spit it out and don't bother buffering it.
			 */
			if (indent + width > max_length) {
				putwchar('\n');
				if (indent > 0)
					output_indent(indent);
		write_out_word:
				wprintf(L"%.*ls", (int)length, word);
				x0 = 0;
				x = indent1;
				pending_spaces = 0;
				output_buffer_length = 0;
			} else {
				wmemcpy(output_buffer, word, length);
				x0 = width;
				x = width + indent1;
				pending_spaces = spaces;
				output_buffer_length = length;
			}
		}
		putwchar('\n');
		output_in_paragraph = 1;
	}
}