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
struct strbuf {char* buf; int len; } ;
struct mailinfo {int input_error; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 scalar_t__ convert_to_utf8 (struct mailinfo*,struct strbuf*,char*) ; 
 struct strbuf* decode_b_segment (struct strbuf*) ; 
 struct strbuf* decode_q_segment (struct strbuf*,int) ; 
 int /*<<< orphan*/  free (struct strbuf*) ; 
 int /*<<< orphan*/  isspace (char) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char*,int) ; 
 int /*<<< orphan*/  strbuf_addbuf (struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 char* strchr (char*,char) ; 
 char* strstr (char*,char*) ; 
 int tolower (int) ; 

__attribute__((used)) static void decode_header(struct mailinfo *mi, struct strbuf *it)
{
	char *in, *ep, *cp;
	struct strbuf outbuf = STRBUF_INIT, *dec;
	struct strbuf charset_q = STRBUF_INIT, piecebuf = STRBUF_INIT;
	int found_error = 1; /* pessimism */

	in = it->buf;
	while (in - it->buf <= it->len && (ep = strstr(in, "=?")) != NULL) {
		int encoding;
		strbuf_reset(&charset_q);
		strbuf_reset(&piecebuf);

		if (in != ep) {
			/*
			 * We are about to process an encoded-word
			 * that begins at ep, but there is something
			 * before the encoded word.
			 */
			char *scan;
			for (scan = in; scan < ep; scan++)
				if (!isspace(*scan))
					break;

			if (scan != ep || in == it->buf) {
				/*
				 * We should not lose that "something",
				 * unless we have just processed an
				 * encoded-word, and there is only LWS
				 * before the one we are about to process.
				 */
				strbuf_add(&outbuf, in, ep - in);
			}
		}
		/* E.g.
		 * ep : "=?iso-2022-jp?B?GyR...?= foo"
		 * ep : "=?ISO-8859-1?Q?Foo=FCbar?= baz"
		 */
		ep += 2;

		if (ep - it->buf >= it->len || !(cp = strchr(ep, '?')))
			goto release_return;

		if (cp + 3 - it->buf > it->len)
			goto release_return;
		strbuf_add(&charset_q, ep, cp - ep);

		encoding = cp[1];
		if (!encoding || cp[2] != '?')
			goto release_return;
		ep = strstr(cp + 3, "?=");
		if (!ep)
			goto release_return;
		strbuf_add(&piecebuf, cp + 3, ep - cp - 3);
		switch (tolower(encoding)) {
		default:
			goto release_return;
		case 'b':
			dec = decode_b_segment(&piecebuf);
			break;
		case 'q':
			dec = decode_q_segment(&piecebuf, 1);
			break;
		}
		if (convert_to_utf8(mi, dec, charset_q.buf))
			goto release_return;

		strbuf_addbuf(&outbuf, dec);
		strbuf_release(dec);
		free(dec);
		in = ep + 2;
	}
	strbuf_addstr(&outbuf, in);
	strbuf_reset(it);
	strbuf_addbuf(it, &outbuf);
	found_error = 0;
release_return:
	strbuf_release(&outbuf);
	strbuf_release(&charset_q);
	strbuf_release(&piecebuf);

	if (found_error)
		mi->input_error = -1;
}