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
struct option {int /*<<< orphan*/ * long_name; int /*<<< orphan*/ * short_name; struct strbuf* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  sq_quote_buf (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stuck_long ; 

__attribute__((used)) static int parseopt_dump(const struct option *o, const char *arg, int unset)
{
	struct strbuf *parsed = o->value;
	if (unset)
		strbuf_addf(parsed, " --no-%s", o->long_name);
	else if (o->short_name && (o->long_name == NULL || !stuck_long))
		strbuf_addf(parsed, " -%c", o->short_name);
	else
		strbuf_addf(parsed, " --%s", o->long_name);
	if (arg) {
		if (!stuck_long)
			strbuf_addch(parsed, ' ');
		else if (o->long_name)
			strbuf_addch(parsed, '=');
		sq_quote_buf(parsed, arg);
	}
	return 0;
}