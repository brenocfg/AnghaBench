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
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,int) ; 
 int /*<<< orphan*/  strbuf_init (struct strbuf*,int /*<<< orphan*/ ) ; 
 struct strbuf* xmalloc (int) ; 

__attribute__((used)) static struct strbuf *decode_b_segment(const struct strbuf *b_seg)
{
	/* Decode in..ep, possibly in-place to ot */
	int c, pos = 0, acc = 0;
	const char *in = b_seg->buf;
	struct strbuf *out = xmalloc(sizeof(struct strbuf));
	strbuf_init(out, b_seg->len);

	while ((c = *in++) != 0) {
		if (c == '+')
			c = 62;
		else if (c == '/')
			c = 63;
		else if ('A' <= c && c <= 'Z')
			c -= 'A';
		else if ('a' <= c && c <= 'z')
			c -= 'a' - 26;
		else if ('0' <= c && c <= '9')
			c -= '0' - 52;
		else
			continue; /* garbage */
		switch (pos++) {
		case 0:
			acc = (c << 2);
			break;
		case 1:
			strbuf_addch(out, (acc | (c >> 4)));
			acc = (c & 15) << 4;
			break;
		case 2:
			strbuf_addch(out, (acc | (c >> 2)));
			acc = (c & 3) << 6;
			break;
		case 3:
			strbuf_addch(out, (acc | c));
			acc = pos = 0;
			break;
		}
	}
	return out;
}