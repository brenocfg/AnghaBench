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
struct strbuf {size_t len; } ;

/* Variables and functions */
 size_t display_mode_esc_sequence_len (char const*) ; 
 int /*<<< orphan*/  isalnum (char const) ; 
 int isspace (char const) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_add_indented_text (struct strbuf*,char const*,int,int) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addchars (struct strbuf*,char,int) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,size_t) ; 
 scalar_t__ utf8_width (char const**,int /*<<< orphan*/ *) ; 

void strbuf_add_wrapped_text(struct strbuf *buf,
		const char *text, int indent1, int indent2, int width)
{
	int indent, w, assume_utf8 = 1;
	const char *bol, *space, *start = text;
	size_t orig_len = buf->len;

	if (width <= 0) {
		strbuf_add_indented_text(buf, text, indent1, indent2);
		return;
	}

retry:
	bol = text;
	w = indent = indent1;
	space = NULL;
	if (indent < 0) {
		w = -indent;
		space = text;
	}

	for (;;) {
		char c;
		size_t skip;

		while ((skip = display_mode_esc_sequence_len(text)))
			text += skip;

		c = *text;
		if (!c || isspace(c)) {
			if (w <= width || !space) {
				const char *start = bol;
				if (!c && text == start)
					return;
				if (space)
					start = space;
				else
					strbuf_addchars(buf, ' ', indent);
				strbuf_add(buf, start, text - start);
				if (!c)
					return;
				space = text;
				if (c == '\t')
					w |= 0x07;
				else if (c == '\n') {
					space++;
					if (*space == '\n') {
						strbuf_addch(buf, '\n');
						goto new_line;
					}
					else if (!isalnum(*space))
						goto new_line;
					else
						strbuf_addch(buf, ' ');
				}
				w++;
				text++;
			}
			else {
new_line:
				strbuf_addch(buf, '\n');
				text = bol = space + isspace(*space);
				space = NULL;
				w = indent = indent2;
			}
			continue;
		}
		if (assume_utf8) {
			w += utf8_width(&text, NULL);
			if (!text) {
				assume_utf8 = 0;
				text = start;
				strbuf_setlen(buf, orig_len);
				goto retry;
			}
		} else {
			w++;
			text++;
		}
	}
}