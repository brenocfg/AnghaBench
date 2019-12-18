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
 int /*<<< orphan*/  sq_quote_buf (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,char const*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char*) ; 

__attribute__((used)) static void add_var(struct strbuf *buf, const char *name, const char *value)
{
	if (!value)
		strbuf_addf(buf, "unset %s; ", name);
	else {
		strbuf_addf(buf, "%s=", name);
		sq_quote_buf(buf, value);
		strbuf_addstr(buf, "; ");
	}
}