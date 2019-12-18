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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 unsigned int WS_BLANK_AT_EOL ; 
 unsigned int WS_CR_AT_EOL ; 
 unsigned int WS_INDENT_WITH_NON_TAB ; 
 unsigned int WS_SPACE_BEFORE_TAB ; 
 unsigned int WS_TAB_IN_INDENT ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fwrite (char const*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ isspace (char const) ; 
 int ws_tab_width (unsigned int) ; 

__attribute__((used)) static unsigned ws_check_emit_1(const char *line, int len, unsigned ws_rule,
				FILE *stream, const char *set,
				const char *reset, const char *ws)
{
	unsigned result = 0;
	int written = 0;
	int trailing_whitespace = -1;
	int trailing_newline = 0;
	int trailing_carriage_return = 0;
	int i;

	/* Logic is simpler if we temporarily ignore the trailing newline. */
	if (len > 0 && line[len - 1] == '\n') {
		trailing_newline = 1;
		len--;
	}
	if ((ws_rule & WS_CR_AT_EOL) &&
	    len > 0 && line[len - 1] == '\r') {
		trailing_carriage_return = 1;
		len--;
	}

	/* Check for trailing whitespace. */
	if (ws_rule & WS_BLANK_AT_EOL) {
		for (i = len - 1; i >= 0; i--) {
			if (isspace(line[i])) {
				trailing_whitespace = i;
				result |= WS_BLANK_AT_EOL;
			}
			else
				break;
		}
	}

	if (trailing_whitespace == -1)
		trailing_whitespace = len;

	/* Check indentation */
	for (i = 0; i < trailing_whitespace; i++) {
		if (line[i] == ' ')
			continue;
		if (line[i] != '\t')
			break;
		if ((ws_rule & WS_SPACE_BEFORE_TAB) && written < i) {
			result |= WS_SPACE_BEFORE_TAB;
			if (stream) {
				fputs(ws, stream);
				fwrite(line + written, i - written, 1, stream);
				fputs(reset, stream);
				fwrite(line + i, 1, 1, stream);
			}
		} else if (ws_rule & WS_TAB_IN_INDENT) {
			result |= WS_TAB_IN_INDENT;
			if (stream) {
				fwrite(line + written, i - written, 1, stream);
				fputs(ws, stream);
				fwrite(line + i, 1, 1, stream);
				fputs(reset, stream);
			}
		} else if (stream) {
			fwrite(line + written, i - written + 1, 1, stream);
		}
		written = i + 1;
	}

	/* Check for indent using non-tab. */
	if ((ws_rule & WS_INDENT_WITH_NON_TAB) && i - written >= ws_tab_width(ws_rule)) {
		result |= WS_INDENT_WITH_NON_TAB;
		if (stream) {
			fputs(ws, stream);
			fwrite(line + written, i - written, 1, stream);
			fputs(reset, stream);
		}
		written = i;
	}

	if (stream) {
		/*
		 * Now the rest of the line starts at "written".
		 * The non-highlighted part ends at "trailing_whitespace".
		 */

		/* Emit non-highlighted (middle) segment. */
		if (trailing_whitespace - written > 0) {
			fputs(set, stream);
			fwrite(line + written,
			    trailing_whitespace - written, 1, stream);
			fputs(reset, stream);
		}

		/* Highlight errors in trailing whitespace. */
		if (trailing_whitespace != len) {
			fputs(ws, stream);
			fwrite(line + trailing_whitespace,
			    len - trailing_whitespace, 1, stream);
			fputs(reset, stream);
		}
		if (trailing_carriage_return)
			fputc('\r', stream);
		if (trailing_newline)
			fputc('\n', stream);
	}
	return result;
}