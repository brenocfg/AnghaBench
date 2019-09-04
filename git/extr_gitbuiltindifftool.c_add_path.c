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
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,size_t) ; 

__attribute__((used)) static void add_path(struct strbuf *buf, size_t base_len, const char *path)
{
	strbuf_setlen(buf, base_len);
	if (buf->len && buf->buf[buf->len - 1] != '/')
		strbuf_addch(buf, '/');
	strbuf_addstr(buf, path);
}