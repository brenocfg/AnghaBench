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
struct ident_split {scalar_t__ tz_end; scalar_t__ date_begin; scalar_t__ mail_end; scalar_t__ mail_begin; scalar_t__ name_end; scalar_t__ name_begin; scalar_t__ tz_begin; scalar_t__ date_end; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDENT_STRICT ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  WANT_AUTHOR_IDENT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  assert_split_ident (struct ident_split*,struct strbuf*) ; 
 scalar_t__ author_message ; 
 int /*<<< orphan*/  author_message_buffer ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  export_one (char*,scalar_t__,scalar_t__,char) ; 
 char* find_commit_header (int /*<<< orphan*/ ,char*,size_t*) ; 
 int /*<<< orphan*/  fmt_ident (char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char const* force_author ; 
 scalar_t__ force_date ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  getenv (char*) ; 
 scalar_t__ parse_force_date (scalar_t__,struct strbuf*) ; 
 int /*<<< orphan*/  set_ident_var (char**,int /*<<< orphan*/ ) ; 
 scalar_t__ split_ident_line (struct ident_split*,char const*,size_t) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  xmemdupz (scalar_t__,scalar_t__) ; 
 char* xstrdup_or_null (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void determine_author_info(struct strbuf *author_ident)
{
	char *name, *email, *date;
	struct ident_split author;

	name = xstrdup_or_null(getenv("GIT_AUTHOR_NAME"));
	email = xstrdup_or_null(getenv("GIT_AUTHOR_EMAIL"));
	date = xstrdup_or_null(getenv("GIT_AUTHOR_DATE"));

	if (author_message) {
		struct ident_split ident;
		size_t len;
		const char *a;

		a = find_commit_header(author_message_buffer, "author", &len);
		if (!a)
			die(_("commit '%s' lacks author header"), author_message);
		if (split_ident_line(&ident, a, len) < 0)
			die(_("commit '%s' has malformed author line"), author_message);

		set_ident_var(&name, xmemdupz(ident.name_begin, ident.name_end - ident.name_begin));
		set_ident_var(&email, xmemdupz(ident.mail_begin, ident.mail_end - ident.mail_begin));

		if (ident.date_begin) {
			struct strbuf date_buf = STRBUF_INIT;
			strbuf_addch(&date_buf, '@');
			strbuf_add(&date_buf, ident.date_begin, ident.date_end - ident.date_begin);
			strbuf_addch(&date_buf, ' ');
			strbuf_add(&date_buf, ident.tz_begin, ident.tz_end - ident.tz_begin);
			set_ident_var(&date, strbuf_detach(&date_buf, NULL));
		}
	}

	if (force_author) {
		struct ident_split ident;

		if (split_ident_line(&ident, force_author, strlen(force_author)) < 0)
			die(_("malformed --author parameter"));
		set_ident_var(&name, xmemdupz(ident.name_begin, ident.name_end - ident.name_begin));
		set_ident_var(&email, xmemdupz(ident.mail_begin, ident.mail_end - ident.mail_begin));
	}

	if (force_date) {
		struct strbuf date_buf = STRBUF_INIT;
		if (parse_force_date(force_date, &date_buf))
			die(_("invalid date format: %s"), force_date);
		set_ident_var(&date, strbuf_detach(&date_buf, NULL));
	}

	strbuf_addstr(author_ident, fmt_ident(name, email, WANT_AUTHOR_IDENT, date,
				IDENT_STRICT));
	assert_split_ident(&author, author_ident);
	export_one("GIT_AUTHOR_NAME", author.name_begin, author.name_end, 0);
	export_one("GIT_AUTHOR_EMAIL", author.mail_begin, author.mail_end, 0);
	export_one("GIT_AUTHOR_DATE", author.date_begin, author.tz_end, '@');
	free(name);
	free(email);
	free(date);
}