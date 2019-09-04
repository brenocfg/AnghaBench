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
struct strbuf {int len; char* buf; } ;

/* Variables and functions */

void strbuf_trim_trailing_newline(struct strbuf *sb)
{
	if (sb->len > 0 && sb->buf[sb->len - 1] == '\n') {
		if (--sb->len > 0 && sb->buf[sb->len - 1] == '\r')
			--sb->len;
		sb->buf[sb->len] = '\0';
	}
}