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
struct strbuf {scalar_t__ len; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 unsigned int WS_BLANK_AT_EOF ; 
 unsigned int WS_BLANK_AT_EOL ; 
 unsigned int WS_INDENT_WITH_NON_TAB ; 
 unsigned int WS_SPACE_BEFORE_TAB ; 
 unsigned int WS_TAB_IN_INDENT ; 
 unsigned int WS_TRAILING_SPACE ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 

char *whitespace_error_string(unsigned ws)
{
	struct strbuf err = STRBUF_INIT;
	if ((ws & WS_TRAILING_SPACE) == WS_TRAILING_SPACE)
		strbuf_addstr(&err, "trailing whitespace");
	else {
		if (ws & WS_BLANK_AT_EOL)
			strbuf_addstr(&err, "trailing whitespace");
		if (ws & WS_BLANK_AT_EOF) {
			if (err.len)
				strbuf_addstr(&err, ", ");
			strbuf_addstr(&err, "new blank line at EOF");
		}
	}
	if (ws & WS_SPACE_BEFORE_TAB) {
		if (err.len)
			strbuf_addstr(&err, ", ");
		strbuf_addstr(&err, "space before tab in indent");
	}
	if (ws & WS_INDENT_WITH_NON_TAB) {
		if (err.len)
			strbuf_addstr(&err, ", ");
		strbuf_addstr(&err, "indent with spaces");
	}
	if (ws & WS_TAB_IN_INDENT) {
		if (err.len)
			strbuf_addstr(&err, ", ");
		strbuf_addstr(&err, "tab in indent");
	}
	return strbuf_detach(&err, NULL);
}