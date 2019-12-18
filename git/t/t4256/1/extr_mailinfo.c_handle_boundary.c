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
struct strbuf {scalar_t__ len; scalar_t__ buf; } ;
struct mailinfo {int input_error; int /*<<< orphan*/  input; int /*<<< orphan*/  p_hdr_data; int /*<<< orphan*/  charset; int /*<<< orphan*/  transfer_encoding; struct strbuf** content; struct strbuf** content_top; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (struct strbuf*) ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  TE_DONTCARE ; 
 int /*<<< orphan*/  check_header (struct mailinfo*,struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  find_boundary (struct mailinfo*,struct strbuf*) ; 
 int /*<<< orphan*/  handle_filter (struct mailinfo*,struct strbuf*) ; 
 int /*<<< orphan*/  memcmp (scalar_t__,char*,int) ; 
 scalar_t__ read_one_header_line (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 scalar_t__ strbuf_getline_lf (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int handle_boundary(struct mailinfo *mi, struct strbuf *line)
{
	struct strbuf newline = STRBUF_INIT;

	strbuf_addch(&newline, '\n');
again:
	if (line->len >= (*(mi->content_top))->len + 2 &&
	    !memcmp(line->buf + (*(mi->content_top))->len, "--", 2)) {
		/* we hit an end boundary */
		/* pop the current boundary off the stack */
		strbuf_release(*(mi->content_top));
		FREE_AND_NULL(*(mi->content_top));

		/* technically won't happen as is_multipart_boundary()
		   will fail first.  But just in case..
		 */
		if (--mi->content_top < mi->content) {
			error("Detected mismatched boundaries, can't recover");
			mi->input_error = -1;
			mi->content_top = mi->content;
			strbuf_release(&newline);
			return 0;
		}
		handle_filter(mi, &newline);
		strbuf_release(&newline);
		if (mi->input_error)
			return 0;

		/* skip to the next boundary */
		if (!find_boundary(mi, line))
			return 0;
		goto again;
	}

	/* set some defaults */
	mi->transfer_encoding = TE_DONTCARE;
	strbuf_reset(&mi->charset);

	/* slurp in this section's info */
	while (read_one_header_line(line, mi->input))
		check_header(mi, line, mi->p_hdr_data, 0);

	strbuf_release(&newline);
	/* replenish line */
	if (strbuf_getline_lf(line, mi->input))
		return 0;
	strbuf_addch(line, '\n');
	return 1;
}