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

/* Variables and functions */
 int hex2chr (char const*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,int) ; 
 int /*<<< orphan*/  strbuf_init (struct strbuf*,int /*<<< orphan*/ ) ; 
 struct strbuf* xmalloc (int) ; 

__attribute__((used)) static struct strbuf *decode_q_segment(const struct strbuf *q_seg, int rfc2047)
{
	const char *in = q_seg->buf;
	int c;
	struct strbuf *out = xmalloc(sizeof(struct strbuf));
	strbuf_init(out, q_seg->len);

	while ((c = *in++) != 0) {
		if (c == '=') {
			int ch, d = *in;
			if (d == '\n' || !d)
				break; /* drop trailing newline */
			ch = hex2chr(in);
			if (ch >= 0) {
				strbuf_addch(out, ch);
				in += 2;
				continue;
			}
			/* garbage -- fall through */
		}
		if (rfc2047 && c == '_') /* rfc2047 4.2 (2) */
			c = 0x20;
		strbuf_addch(out, c);
	}
	return out;
}