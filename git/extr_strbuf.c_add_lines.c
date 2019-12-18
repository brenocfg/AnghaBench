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
struct strbuf {int dummy; } ;

/* Variables and functions */
 char* memchr (char const*,char,size_t) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_complete_line (struct strbuf*) ; 

__attribute__((used)) static void add_lines(struct strbuf *out,
			const char *prefix1,
			const char *prefix2,
			const char *buf, size_t size)
{
	while (size) {
		const char *prefix;
		const char *next = memchr(buf, '\n', size);
		next = next ? (next + 1) : (buf + size);

		prefix = ((prefix2 && (buf[0] == '\n' || buf[0] == '\t'))
			  ? prefix2 : prefix1);
		strbuf_addstr(out, prefix);
		strbuf_add(out, buf, next - buf);
		size -= next - buf;
		buf = next;
	}
	strbuf_complete_line(out);
}