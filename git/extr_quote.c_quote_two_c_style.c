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
 scalar_t__ quote_c_style (char const*,struct strbuf*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 

void quote_two_c_style(struct strbuf *sb, const char *prefix, const char *path, int nodq)
{
	if (quote_c_style(prefix, NULL, NULL, 0) ||
	    quote_c_style(path, NULL, NULL, 0)) {
		if (!nodq)
			strbuf_addch(sb, '"');
		quote_c_style(prefix, sb, NULL, 1);
		quote_c_style(path, sb, NULL, 1);
		if (!nodq)
			strbuf_addch(sb, '"');
	} else {
		strbuf_addstr(sb, prefix);
		strbuf_addstr(sb, path);
	}
}