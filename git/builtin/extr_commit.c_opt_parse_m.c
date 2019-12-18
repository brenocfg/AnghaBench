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
struct strbuf {scalar_t__ len; } ;
struct option {struct strbuf* value; } ;

/* Variables and functions */
 int have_option_m ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_complete_line (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int opt_parse_m(const struct option *opt, const char *arg, int unset)
{
	struct strbuf *buf = opt->value;
	if (unset) {
		have_option_m = 0;
		strbuf_setlen(buf, 0);
	} else {
		have_option_m = 1;
		if (buf->len)
			strbuf_addch(buf, '\n');
		strbuf_addstr(buf, arg);
		strbuf_complete_line(buf);
	}
	return 0;
}