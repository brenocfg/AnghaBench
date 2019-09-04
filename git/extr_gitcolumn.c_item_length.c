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
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_remove (struct strbuf*,int,int) ; 
 int strspn (char const*,char*) ; 
 char* strstr (char const*,char*) ; 
 int utf8_strwidth (char const*) ; 

__attribute__((used)) static int item_length(const char *s)
{
	int len, i = 0;
	struct strbuf str = STRBUF_INIT;

	strbuf_addstr(&str, s);
	while ((s = strstr(str.buf + i, "\033[")) != NULL) {
		int len = strspn(s + 2, "0123456789;");
		i = s - str.buf;
		strbuf_remove(&str, i, len + 3); /* \033[<len><func char> */
	}
	len = utf8_strwidth(str.buf);
	strbuf_release(&str);
	return len;
}