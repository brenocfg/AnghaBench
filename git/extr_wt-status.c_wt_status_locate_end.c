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
struct strbuf {scalar_t__ buf; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  comment_line_char ; 
 int /*<<< orphan*/  cut_line ; 
 scalar_t__ starts_with (char const*,scalar_t__) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 char* strstr (char const*,scalar_t__) ; 

size_t wt_status_locate_end(const char *s, size_t len)
{
	const char *p;
	struct strbuf pattern = STRBUF_INIT;

	strbuf_addf(&pattern, "\n%c %s", comment_line_char, cut_line);
	if (starts_with(s, pattern.buf + 1))
		len = 0;
	else if ((p = strstr(s, pattern.buf)))
		len = p - s + 1;
	strbuf_release(&pattern);
	return len;
}