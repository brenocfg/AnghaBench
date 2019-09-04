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
struct object_id {int dummy; } ;

/* Variables and functions */
 int PARSE_SHA1_ALLOW_EMPTY ; 
 int PARSE_SHA1_OLD ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  die (char*,char const*,char const*,...) ; 
 scalar_t__ get_oid (char const*,struct object_id*) ; 
 char line_termination ; 
 int /*<<< orphan*/  oidclr (struct object_id*) ; 
 char* parse_arg (char const*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  warning (char*,char const*,char const*) ; 

__attribute__((used)) static int parse_next_oid(struct strbuf *input, const char **next,
			  struct object_id *oid,
			  const char *command, const char *refname,
			  int flags)
{
	struct strbuf arg = STRBUF_INIT;
	int ret = 0;

	if (*next == input->buf + input->len)
		goto eof;

	if (line_termination) {
		/* Without -z, consume SP and use next argument */
		if (!**next || **next == line_termination)
			return 1;
		if (**next != ' ')
			die("%s %s: expected SP but got: %s",
			    command, refname, *next);
		(*next)++;
		*next = parse_arg(*next, &arg);
		if (arg.len) {
			if (get_oid(arg.buf, oid))
				goto invalid;
		} else {
			/* Without -z, an empty value means all zeros: */
			oidclr(oid);
		}
	} else {
		/* With -z, read the next NUL-terminated line */
		if (**next)
			die("%s %s: expected NUL but got: %s",
			    command, refname, *next);
		(*next)++;
		if (*next == input->buf + input->len)
			goto eof;
		strbuf_addstr(&arg, *next);
		*next += arg.len;

		if (arg.len) {
			if (get_oid(arg.buf, oid))
				goto invalid;
		} else if (flags & PARSE_SHA1_ALLOW_EMPTY) {
			/* With -z, treat an empty value as all zeros: */
			warning("%s %s: missing <newvalue>, treating as zero",
				command, refname);
			oidclr(oid);
		} else {
			/*
			 * With -z, an empty non-required value means
			 * unspecified:
			 */
			ret = 1;
		}
	}

	strbuf_release(&arg);

	return ret;

 invalid:
	die(flags & PARSE_SHA1_OLD ?
	    "%s %s: invalid <oldvalue>: %s" :
	    "%s %s: invalid <newvalue>: %s",
	    command, refname, arg.buf);

 eof:
	die(flags & PARSE_SHA1_OLD ?
	    "%s %s: unexpected end of input when reading <oldvalue>" :
	    "%s %s: unexpected end of input when reading <newvalue>",
	    command, refname);
}