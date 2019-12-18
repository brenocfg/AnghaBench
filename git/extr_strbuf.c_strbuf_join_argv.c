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
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 

const char *strbuf_join_argv(struct strbuf *buf,
			     int argc, const char **argv, char delim)
{
	if (!argc)
		return buf->buf;

	strbuf_addstr(buf, *argv);
	while (--argc) {
		strbuf_addch(buf, delim);
		strbuf_addstr(buf, *(++argv));
	}

	return buf->buf;
}