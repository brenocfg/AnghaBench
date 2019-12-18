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
typedef  scalar_t__ align_type ;

/* Variables and functions */
 scalar_t__ ALIGN_LEFT ; 
 scalar_t__ ALIGN_MIDDLE ; 
 scalar_t__ ALIGN_RIGHT ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,unsigned int,char const*,...) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int strlen (char const*) ; 
 int utf8_strnwidth (char const*,int,int /*<<< orphan*/ ) ; 

void strbuf_utf8_align(struct strbuf *buf, align_type position, unsigned int width,
		       const char *s)
{
	int slen = strlen(s);
	int display_len = utf8_strnwidth(s, slen, 0);
	int utf8_compensation = slen - display_len;

	if (display_len >= width) {
		strbuf_addstr(buf, s);
		return;
	}

	if (position == ALIGN_LEFT)
		strbuf_addf(buf, "%-*s", width + utf8_compensation, s);
	else if (position == ALIGN_MIDDLE) {
		int left = (width - display_len) / 2;
		strbuf_addf(buf, "%*s%-*s", left, "", width - left + utf8_compensation, s);
	} else if (position == ALIGN_RIGHT)
		strbuf_addf(buf, "%*s", width + utf8_compensation, s);
}