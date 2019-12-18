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
struct strbuf {char* buf; scalar_t__ len; } ;
struct mailinfo {int transfer_encoding; scalar_t__ input_error; scalar_t__* content_top; int /*<<< orphan*/  input; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
#define  TE_BASE64 129 
#define  TE_QP 128 
 int /*<<< orphan*/  decode_transfer_encoding (struct mailinfo*,struct strbuf*) ; 
 int /*<<< orphan*/  find_boundary (struct mailinfo*,struct strbuf*) ; 
 int /*<<< orphan*/  flush_inbody_header_accum (struct mailinfo*) ; 
 int /*<<< orphan*/  handle_boundary (struct mailinfo*,struct strbuf*) ; 
 int /*<<< orphan*/  handle_filter (struct mailinfo*,struct strbuf*) ; 
 int /*<<< orphan*/  handle_filter_flowed (struct mailinfo*,struct strbuf*,struct strbuf*) ; 
 scalar_t__ is_multipart_boundary (struct mailinfo*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addbuf (struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_getwholeline (struct strbuf*,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  strbuf_insert (struct strbuf*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  strbuf_list_free (struct strbuf**) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 struct strbuf** strbuf_split (struct strbuf*,char) ; 

__attribute__((used)) static void handle_body(struct mailinfo *mi, struct strbuf *line)
{
	struct strbuf prev = STRBUF_INIT;

	/* Skip up to the first boundary */
	if (*(mi->content_top)) {
		if (!find_boundary(mi, line))
			goto handle_body_out;
	}

	do {
		/* process any boundary lines */
		if (*(mi->content_top) && is_multipart_boundary(mi, line)) {
			/* flush any leftover */
			if (prev.len) {
				handle_filter(mi, &prev);
				strbuf_reset(&prev);
			}
			if (!handle_boundary(mi, line))
				goto handle_body_out;
		}

		/* Unwrap transfer encoding */
		decode_transfer_encoding(mi, line);

		switch (mi->transfer_encoding) {
		case TE_BASE64:
		case TE_QP:
		{
			struct strbuf **lines, **it, *sb;

			/* Prepend any previous partial lines */
			strbuf_insert(line, 0, prev.buf, prev.len);
			strbuf_reset(&prev);

			/*
			 * This is a decoded line that may contain
			 * multiple new lines.  Pass only one chunk
			 * at a time to handle_filter()
			 */
			lines = strbuf_split(line, '\n');
			for (it = lines; (sb = *it); it++) {
				if (*(it + 1) == NULL) /* The last line */
					if (sb->buf[sb->len - 1] != '\n') {
						/* Partial line, save it for later. */
						strbuf_addbuf(&prev, sb);
						break;
					}
				handle_filter_flowed(mi, sb, &prev);
			}
			/*
			 * The partial chunk is saved in "prev" and will be
			 * appended by the next iteration of read_line_with_nul().
			 */
			strbuf_list_free(lines);
			break;
		}
		default:
			handle_filter_flowed(mi, line, &prev);
		}

		if (mi->input_error)
			break;
	} while (!strbuf_getwholeline(line, mi->input, '\n'));

	if (prev.len)
		handle_filter(mi, &prev);

	flush_inbody_header_accum(mi);

handle_body_out:
	strbuf_release(&prev);
}