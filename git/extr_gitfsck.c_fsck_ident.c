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
struct object {int dummy; } ;
struct fsck_options {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSCK_MSG_BAD_DATE ; 
 int /*<<< orphan*/  FSCK_MSG_BAD_DATE_OVERFLOW ; 
 int /*<<< orphan*/  FSCK_MSG_BAD_EMAIL ; 
 int /*<<< orphan*/  FSCK_MSG_BAD_NAME ; 
 int /*<<< orphan*/  FSCK_MSG_BAD_TIMEZONE ; 
 int /*<<< orphan*/  FSCK_MSG_MISSING_EMAIL ; 
 int /*<<< orphan*/  FSCK_MSG_MISSING_NAME_BEFORE_EMAIL ; 
 int /*<<< orphan*/  FSCK_MSG_MISSING_SPACE_BEFORE_DATE ; 
 int /*<<< orphan*/  FSCK_MSG_MISSING_SPACE_BEFORE_EMAIL ; 
 int /*<<< orphan*/  FSCK_MSG_ZERO_PADDED_DATE ; 
 scalar_t__ date_overflows (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isdigit (char const) ; 
 int /*<<< orphan*/  parse_timestamp (char const*,char**,int) ; 
 int report (struct fsck_options*,struct object*,int /*<<< orphan*/ ,char*) ; 
 char* strchrnul (char const*,char) ; 
 int /*<<< orphan*/  strcspn (char const*,char*) ; 

__attribute__((used)) static int fsck_ident(const char **ident, struct object *obj, struct fsck_options *options)
{
	const char *p = *ident;
	char *end;

	*ident = strchrnul(*ident, '\n');
	if (**ident == '\n')
		(*ident)++;

	if (*p == '<')
		return report(options, obj, FSCK_MSG_MISSING_NAME_BEFORE_EMAIL, "invalid author/committer line - missing space before email");
	p += strcspn(p, "<>\n");
	if (*p == '>')
		return report(options, obj, FSCK_MSG_BAD_NAME, "invalid author/committer line - bad name");
	if (*p != '<')
		return report(options, obj, FSCK_MSG_MISSING_EMAIL, "invalid author/committer line - missing email");
	if (p[-1] != ' ')
		return report(options, obj, FSCK_MSG_MISSING_SPACE_BEFORE_EMAIL, "invalid author/committer line - missing space before email");
	p++;
	p += strcspn(p, "<>\n");
	if (*p != '>')
		return report(options, obj, FSCK_MSG_BAD_EMAIL, "invalid author/committer line - bad email");
	p++;
	if (*p != ' ')
		return report(options, obj, FSCK_MSG_MISSING_SPACE_BEFORE_DATE, "invalid author/committer line - missing space before date");
	p++;
	if (*p == '0' && p[1] != ' ')
		return report(options, obj, FSCK_MSG_ZERO_PADDED_DATE, "invalid author/committer line - zero-padded date");
	if (date_overflows(parse_timestamp(p, &end, 10)))
		return report(options, obj, FSCK_MSG_BAD_DATE_OVERFLOW, "invalid author/committer line - date causes integer overflow");
	if ((end == p || *end != ' '))
		return report(options, obj, FSCK_MSG_BAD_DATE, "invalid author/committer line - bad date");
	p = end + 1;
	if ((*p != '+' && *p != '-') ||
	    !isdigit(p[1]) ||
	    !isdigit(p[2]) ||
	    !isdigit(p[3]) ||
	    !isdigit(p[4]) ||
	    (p[5] != '\n'))
		return report(options, obj, FSCK_MSG_BAD_TIMEZONE, "invalid author/committer line - bad time zone");
	p += 6;
	return 0;
}