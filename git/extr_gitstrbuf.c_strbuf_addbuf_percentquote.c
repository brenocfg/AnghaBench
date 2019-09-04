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
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 

void strbuf_addbuf_percentquote(struct strbuf *dst, const struct strbuf *src)
{
	size_t i, len = src->len;

	for (i = 0; i < len; i++) {
		if (src->buf[i] == '%')
			strbuf_addch(dst, '%');
		strbuf_addch(dst, src->buf[i]);
	}
}