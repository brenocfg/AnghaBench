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
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 

__attribute__((used)) static void add_flattened_path(struct strbuf *out, const char *s)
{
	size_t i = out->len;
	strbuf_addstr(out, s);
	for (; i < out->len; i++)
		if (out->buf[i] == '/')
			out->buf[i] = '_';
}