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
struct strbuf {int /*<<< orphan*/  buf; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  REFNAME_ALLOW_ONELEVEL ; 
 struct strbuf STRBUF_INIT ; 
 scalar_t__ check_refname_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ line_termination ; 
 char* parse_arg (char const*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static char *parse_refname(struct strbuf *input, const char **next)
{
	struct strbuf ref = STRBUF_INIT;

	if (line_termination) {
		/* Without -z, use the next argument */
		*next = parse_arg(*next, &ref);
	} else {
		/* With -z, use everything up to the next NUL */
		strbuf_addstr(&ref, *next);
		*next += ref.len;
	}

	if (!ref.len) {
		strbuf_release(&ref);
		return NULL;
	}

	if (check_refname_format(ref.buf, REFNAME_ALLOW_ONELEVEL))
		die("invalid ref format: %s", ref.buf);

	return strbuf_detach(&ref, NULL);
}