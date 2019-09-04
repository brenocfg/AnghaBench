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
 int /*<<< orphan*/  count_ident (char const*,size_t) ; 
 char* memchr (char const*,char,int) ; 
 int /*<<< orphan*/  memcmp (char const*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memmove (char*,char const*,size_t) ; 
 size_t strbuf_avail (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_grow (struct strbuf*,size_t) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 

__attribute__((used)) static int ident_to_git(const char *src, size_t len,
			struct strbuf *buf, int ident)
{
	char *dst, *dollar;

	if (!ident || (src && !count_ident(src, len)))
		return 0;

	if (!buf)
		return 1;

	/* only grow if not in place */
	if (strbuf_avail(buf) + buf->len < len)
		strbuf_grow(buf, len - buf->len);
	dst = buf->buf;
	for (;;) {
		dollar = memchr(src, '$', len);
		if (!dollar)
			break;
		memmove(dst, src, dollar + 1 - src);
		dst += dollar + 1 - src;
		len -= dollar + 1 - src;
		src  = dollar + 1;

		if (len > 3 && !memcmp(src, "Id:", 3)) {
			dollar = memchr(src + 3, '$', len - 3);
			if (!dollar)
				break;
			if (memchr(src + 3, '\n', dollar - src - 3)) {
				/* Line break before the next dollar. */
				continue;
			}

			memcpy(dst, "Id$", 3);
			dst += 3;
			len -= dollar + 1 - src;
			src  = dollar + 1;
		}
	}
	memmove(dst, src, len);
	strbuf_setlen(buf, dst + len - buf->buf);
	return 1;
}