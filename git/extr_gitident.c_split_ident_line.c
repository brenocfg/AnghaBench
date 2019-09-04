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
struct ident_split {char const* name_begin; char const* mail_begin; char const* name_end; char const* mail_end; char const* date_begin; char const* date_end; char const* tz_begin; char const* tz_end; } ;

/* Variables and functions */
 scalar_t__ isspace (char const) ; 
 int /*<<< orphan*/  memset (struct ident_split*,int /*<<< orphan*/ ,int) ; 
 size_t strspn (char const*,char*) ; 

int split_ident_line(struct ident_split *split, const char *line, int len)
{
	const char *cp;
	size_t span;
	int status = -1;

	memset(split, 0, sizeof(*split));

	split->name_begin = line;
	for (cp = line; *cp && cp < line + len; cp++)
		if (*cp == '<') {
			split->mail_begin = cp + 1;
			break;
		}
	if (!split->mail_begin)
		return status;

	for (cp = split->mail_begin - 2; line <= cp; cp--)
		if (!isspace(*cp)) {
			split->name_end = cp + 1;
			break;
		}
	if (!split->name_end) {
		/* no human readable name */
		split->name_end = split->name_begin;
	}

	for (cp = split->mail_begin; cp < line + len; cp++)
		if (*cp == '>') {
			split->mail_end = cp;
			break;
		}
	if (!split->mail_end)
		return status;

	/*
	 * Look from the end-of-line to find the trailing ">" of the mail
	 * address, even though we should already know it as split->mail_end.
	 * This can help in cases of broken idents with an extra ">" somewhere
	 * in the email address.  Note that we are assuming the timestamp will
	 * never have a ">" in it.
	 *
	 * Note that we will always find some ">" before going off the front of
	 * the string, because will always hit the split->mail_end closing
	 * bracket.
	 */
	for (cp = line + len - 1; *cp != '>'; cp--)
		;

	for (cp = cp + 1; cp < line + len && isspace(*cp); cp++)
		;
	if (line + len <= cp)
		goto person_only;
	split->date_begin = cp;
	span = strspn(cp, "0123456789");
	if (!span)
		goto person_only;
	split->date_end = split->date_begin + span;
	for (cp = split->date_end; cp < line + len && isspace(*cp); cp++)
		;
	if (line + len <= cp || (*cp != '+' && *cp != '-'))
		goto person_only;
	split->tz_begin = cp;
	span = strspn(cp + 1, "0123456789");
	if (!span)
		goto person_only;
	split->tz_end = split->tz_begin + 1 + span;
	return 0;

person_only:
	split->date_begin = NULL;
	split->date_end = NULL;
	split->tz_begin = NULL;
	split->tz_end = NULL;
	return 0;
}