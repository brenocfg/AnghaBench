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
struct strbuf {char* buf; int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 struct strbuf STRBUF_INIT ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_rfc2822_header (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addbuf (struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 scalar_t__ strbuf_getline_lf (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_rtrim (struct strbuf*) ; 
 int /*<<< orphan*/  ungetc (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_one_header_line(struct strbuf *line, FILE *in)
{
	struct strbuf continuation = STRBUF_INIT;

	/* Get the first part of the line. */
	if (strbuf_getline_lf(line, in))
		return 0;

	/*
	 * Is it an empty line or not a valid rfc2822 header?
	 * If so, stop here, and return false ("not a header")
	 */
	strbuf_rtrim(line);
	if (!line->len || !is_rfc2822_header(line)) {
		/* Re-add the newline */
		strbuf_addch(line, '\n');
		return 0;
	}

	/*
	 * Now we need to eat all the continuation lines..
	 * Yuck, 2822 header "folding"
	 */
	for (;;) {
		int peek;

		peek = fgetc(in);
		if (peek == EOF)
			break;
		ungetc(peek, in);
		if (peek != ' ' && peek != '\t')
			break;
		if (strbuf_getline_lf(&continuation, in))
			break;
		continuation.buf[0] = ' ';
		strbuf_rtrim(&continuation);
		strbuf_addbuf(line, &continuation);
	}
	strbuf_release(&continuation);

	return 1;
}