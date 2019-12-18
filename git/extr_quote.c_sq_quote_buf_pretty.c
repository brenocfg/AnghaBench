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
 int /*<<< orphan*/  isalpha (char const) ; 
 int /*<<< orphan*/  isdigit (char const) ; 
 int /*<<< orphan*/  sq_quote_buf (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strchr (char const*,char const) ; 

void sq_quote_buf_pretty(struct strbuf *dst, const char *src)
{
	static const char ok_punct[] = "+,-./:=@_^";
	const char *p;

	/* Avoid losing a zero-length string by adding '' */
	if (!*src) {
		strbuf_addstr(dst, "''");
		return;
	}

	for (p = src; *p; p++) {
		if (!isalpha(*p) && !isdigit(*p) && !strchr(ok_punct, *p)) {
			sq_quote_buf(dst, src);
			return;
		}
	}

	/* if we get here, we did not need quoting */
	strbuf_addstr(dst, src);
}