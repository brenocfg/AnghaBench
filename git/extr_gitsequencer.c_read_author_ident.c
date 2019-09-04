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
struct strbuf {char const* buf; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  WANT_AUTHOR_IDENT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  fmt_ident (char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ parse_date (char*,struct strbuf*) ; 
 scalar_t__ read_author_script (int /*<<< orphan*/ ,char**,char**,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rebase_path_author_script () ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_swap (struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *read_author_ident(struct strbuf *buf)
{
	struct strbuf out = STRBUF_INIT;
	char *name, *email, *date;

	if (read_author_script(rebase_path_author_script(),
			       &name, &email, &date, 0))
		return NULL;

	/* validate date since fmt_ident() will die() on bad value */
	if (parse_date(date, &out)){
		warning(_("invalid date format '%s' in '%s'"),
			date, rebase_path_author_script());
		strbuf_release(&out);
		return NULL;
	}

	strbuf_reset(&out);
	strbuf_addstr(&out, fmt_ident(name, email, WANT_AUTHOR_IDENT, date, 0));
	strbuf_swap(buf, &out);
	strbuf_release(&out);
	free(name);
	free(email);
	free(date);
	return buf->buf;
}