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
struct strbuf {size_t len; char* buf; } ;

/* Variables and functions */
 unsigned int APPEND_SIGNOFF_DEDUP ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  WANT_COMMITTER_IDENT ; 
 int /*<<< orphan*/  fmt_name (int /*<<< orphan*/ ) ; 
 int has_conforming_footer (struct strbuf*,struct strbuf*,size_t) ; 
 int /*<<< orphan*/  sign_off_header ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_complete_line (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_splice (struct strbuf*,size_t,int /*<<< orphan*/ ,char const*,size_t) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,size_t) ; 

void append_signoff(struct strbuf *msgbuf, size_t ignore_footer, unsigned flag)
{
	unsigned no_dup_sob = flag & APPEND_SIGNOFF_DEDUP;
	struct strbuf sob = STRBUF_INIT;
	int has_footer;

	strbuf_addstr(&sob, sign_off_header);
	strbuf_addstr(&sob, fmt_name(WANT_COMMITTER_IDENT));
	strbuf_addch(&sob, '\n');

	if (!ignore_footer)
		strbuf_complete_line(msgbuf);

	/*
	 * If the whole message buffer is equal to the sob, pretend that we
	 * found a conforming footer with a matching sob
	 */
	if (msgbuf->len - ignore_footer == sob.len &&
	    !strncmp(msgbuf->buf, sob.buf, sob.len))
		has_footer = 3;
	else
		has_footer = has_conforming_footer(msgbuf, &sob, ignore_footer);

	if (!has_footer) {
		const char *append_newlines = NULL;
		size_t len = msgbuf->len - ignore_footer;

		if (!len) {
			/*
			 * The buffer is completely empty.  Leave foom for
			 * the title and body to be filled in by the user.
			 */
			append_newlines = "\n\n";
		} else if (len == 1) {
			/*
			 * Buffer contains a single newline.  Add another
			 * so that we leave room for the title and body.
			 */
			append_newlines = "\n";
		} else if (msgbuf->buf[len - 2] != '\n') {
			/*
			 * Buffer ends with a single newline.  Add another
			 * so that there is an empty line between the message
			 * body and the sob.
			 */
			append_newlines = "\n";
		} /* else, the buffer already ends with two newlines. */

		if (append_newlines)
			strbuf_splice(msgbuf, msgbuf->len - ignore_footer, 0,
				append_newlines, strlen(append_newlines));
	}

	if (has_footer != 3 && (!no_dup_sob || has_footer != 2))
		strbuf_splice(msgbuf, msgbuf->len - ignore_footer, 0,
				sob.buf, sob.len);

	strbuf_release(&sob);
}