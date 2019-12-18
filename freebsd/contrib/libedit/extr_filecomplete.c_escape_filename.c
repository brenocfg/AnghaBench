#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
struct TYPE_4__ {char* buffer; char* cursor; } ;
struct TYPE_5__ {TYPE_1__ el_line; } ;
typedef  TYPE_2__ EditLine ;

/* Variables and functions */
 char* el_malloc (size_t) ; 
 scalar_t__ needs_dquote_escaping (char) ; 
 scalar_t__ needs_escaping (char) ; 

__attribute__((used)) static char *
escape_filename(EditLine * el, const char *filename, int single_match,
		const char *(*app_func)(const char *))
{
	size_t original_len = 0;
	size_t escaped_character_count = 0;
	size_t offset = 0;
	size_t newlen;
	const char *s;
	char c;
	size_t s_quoted = 0;	/* does the input contain a single quote */
	size_t d_quoted = 0;	/* does the input contain a double quote */
	char *escaped_str;
	wchar_t *temp = el->el_line.buffer;
	const char *append_char = NULL;

	if (filename == NULL)
		return NULL;

	while (temp != el->el_line.cursor) {
		/*
		 * If we see a single quote but have not seen a double quote
		 * so far set/unset s_quote
		 */
		if (temp[0] == '\'' && !d_quoted)
			s_quoted = !s_quoted;
		/*
		 * vice versa to the above condition
		 */
		else if (temp[0] == '"' && !s_quoted)
			d_quoted = !d_quoted;
		temp++;
	}

	/* Count number of special characters so that we can calculate
	 * number of extra bytes needed in the new string
	 */
	for (s = filename; *s; s++, original_len++) {
		c = *s;
		/* Inside a single quote only single quotes need escaping */
		if (s_quoted && c == '\'') {
			escaped_character_count += 3;
			continue;
		}
		/* Inside double quotes only ", \, ` and $ need escaping */
		if (d_quoted && needs_dquote_escaping(c)) {
			escaped_character_count++;
			continue;
		}
		if (!s_quoted && !d_quoted && needs_escaping(c))
			escaped_character_count++;
	}

	newlen = original_len + escaped_character_count + 1;
	if (s_quoted || d_quoted)
		newlen++;

	if (single_match && app_func)
		newlen++;

	if ((escaped_str = el_malloc(newlen)) == NULL)
		return NULL;

	for (s = filename; *s; s++) {
		c = *s;
		if (!needs_escaping(c)) {
			/* no escaping is required continue as usual */
			escaped_str[offset++] = c;
			continue;
		}

		/* single quotes inside single quotes require special handling */
		if (c == '\'' && s_quoted) {
			escaped_str[offset++] = '\'';
			escaped_str[offset++] = '\\';
			escaped_str[offset++] = '\'';
			escaped_str[offset++] = '\'';
			continue;
		}

		/* Otherwise no escaping needed inside single quotes */
		if (s_quoted) {
			escaped_str[offset++] = c;
			continue;
		}

		/* No escaping needed inside a double quoted string either
		 * unless we see a '$', '\', '`', or '"' (itself)
		 */
		if (d_quoted && !needs_dquote_escaping(c)) {
			escaped_str[offset++] = c;
			continue;
		}

		/* If we reach here that means escaping is actually needed */
		escaped_str[offset++] = '\\';
		escaped_str[offset++] = c;
	}

	if (single_match && app_func) {
		escaped_str[offset] = 0;
		append_char = app_func(escaped_str);
		/* we want to append space only if we are not inside quotes */
		if (append_char[0] == ' ') {
			if (!s_quoted && !d_quoted)
				escaped_str[offset++] = append_char[0];
		} else
			escaped_str[offset++] = append_char[0];
	}

	/* close the quotes if single match and the match is not a directory */
	if (single_match && (append_char && append_char[0] == ' ')) { 
		if (s_quoted)
			escaped_str[offset++] = '\'';
		else if (d_quoted)
			escaped_str[offset++] = '"';
	}

	escaped_str[offset] = 0;
	return escaped_str;
}