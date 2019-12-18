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
 size_t date_len (char const*,int) ; 
 size_t fractional_time_len (char const*,int) ; 
 int /*<<< orphan*/  isdigit (char const) ; 
 size_t sane_tz_len (char const*,int) ; 
 size_t short_time_len (char const*,int) ; 
 int /*<<< orphan*/  trailing_spaces_len (char const*,int) ; 
 size_t tz_with_colon_len (char const*,int) ; 

__attribute__((used)) static size_t diff_timestamp_len(const char *line, size_t len)
{
	const char *end = line + len;
	size_t n;

	/*
	 * Posix: 2010-07-05 19:41:17
	 * GNU: 2010-07-05 19:41:17.620000023 -0500
	 */

	if (!isdigit(end[-1]))
		return 0;

	n = sane_tz_len(line, end - line);
	if (!n)
		n = tz_with_colon_len(line, end - line);
	end -= n;

	n = short_time_len(line, end - line);
	if (!n)
		n = fractional_time_len(line, end - line);
	end -= n;

	n = date_len(line, end - line);
	if (!n)	/* No date.  Too bad. */
		return 0;
	end -= n;

	if (end == line)	/* No space before date. */
		return 0;
	if (end[-1] == '\t') {	/* Success! */
		end--;
		return line + len - end;
	}
	if (end[-1] != ' ')	/* No space before date. */
		return 0;

	/* Whitespace damage. */
	end -= trailing_spaces_len(line, end - line);
	return line + len - end;
}