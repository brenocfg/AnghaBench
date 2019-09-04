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
struct string_list_item {char* util; } ;
struct string_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REFNAME_ALLOW_ONELEVEL ; 
 scalar_t__ check_refname_format (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strchr (char*,char) ; 
 struct string_list_item* string_list_append_nodup (struct string_list*,char*) ; 
 char* xmemdupz (char const*,int) ; 

__attribute__((used)) static void parse_one_symref_info(struct string_list *symref, const char *val, int len)
{
	char *sym, *target;
	struct string_list_item *item;

	if (!len)
		return; /* just "symref" */
	/* e.g. "symref=HEAD:refs/heads/master" */
	sym = xmemdupz(val, len);
	target = strchr(sym, ':');
	if (!target)
		/* just "symref=something" */
		goto reject;
	*(target++) = '\0';
	if (check_refname_format(sym, REFNAME_ALLOW_ONELEVEL) ||
	    check_refname_format(target, REFNAME_ALLOW_ONELEVEL))
		/* "symref=bogus:pair */
		goto reject;
	item = string_list_append_nodup(symref, sym);
	item->util = target;
	return;
reject:
	free(sym);
	return;
}