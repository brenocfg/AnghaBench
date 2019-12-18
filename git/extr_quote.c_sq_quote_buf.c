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
struct strbuf {char const* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ need_bs_quote (char const) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,size_t) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 size_t strcspn (char const*,char*) ; 

void sq_quote_buf(struct strbuf *dst, const char *src)
{
	char *to_free = NULL;

	if (dst->buf == src)
		to_free = strbuf_detach(dst, NULL);

	strbuf_addch(dst, '\'');
	while (*src) {
		size_t len = strcspn(src, "'!");
		strbuf_add(dst, src, len);
		src += len;
		while (need_bs_quote(*src)) {
			strbuf_addstr(dst, "'\\");
			strbuf_addch(dst, *src++);
			strbuf_addch(dst, '\'');
		}
	}
	strbuf_addch(dst, '\'');
	free(to_free);
}