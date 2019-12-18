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
struct strbuf {char const* buf; int len; } ;

/* Variables and functions */
 scalar_t__ ends_with (char const*,char const*) ; 
 int /*<<< orphan*/  strbuf_splice (struct strbuf*,int,int,char const*,int) ; 
 int strlen (char const*) ; 
 char* strstr (char const*,char const*) ; 

__attribute__((used)) static int find_and_replace(struct strbuf *haystack,
			    const char *needle,
			    const char *placeholder)
{
	const char *p = NULL;
	int plen, nlen;

	nlen = strlen(needle);
	if (ends_with(haystack->buf, needle))
		p = haystack->buf + haystack->len - nlen;
	else
		p = strstr(haystack->buf, needle);
	if (!p)
		return 0;

	if (p > haystack->buf && p[-1] != '/')
		return 0;

	plen = strlen(p);
	if (plen > nlen && p[nlen] != '/')
		return 0;

	strbuf_splice(haystack, p - haystack->buf, nlen,
		      placeholder, strlen(placeholder));
	return 1;
}