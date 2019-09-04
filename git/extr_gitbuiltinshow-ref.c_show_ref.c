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
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  found_match ; 
 scalar_t__ heads_only ; 
 scalar_t__ memcmp (char const*,char const*,int) ; 
 char** pattern ; 
 scalar_t__ show_head ; 
 int /*<<< orphan*/  show_one (char const*,struct object_id const*) ; 
 scalar_t__ starts_with (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int strlen (char const*) ; 
 scalar_t__ tags_only ; 

__attribute__((used)) static int show_ref(const char *refname, const struct object_id *oid,
		    int flag, void *cbdata)
{
	if (show_head && !strcmp(refname, "HEAD"))
		goto match;

	if (tags_only || heads_only) {
		int match;

		match = heads_only && starts_with(refname, "refs/heads/");
		match |= tags_only && starts_with(refname, "refs/tags/");
		if (!match)
			return 0;
	}
	if (pattern) {
		int reflen = strlen(refname);
		const char **p = pattern, *m;
		while ((m = *p++) != NULL) {
			int len = strlen(m);
			if (len > reflen)
				continue;
			if (memcmp(m, refname + reflen - len, len))
				continue;
			if (len == reflen)
				goto match;
			if (refname[reflen - len - 1] == '/')
				goto match;
		}
		return 0;
	}

match:
	found_match++;

	show_one(refname, oid);

	return 0;
}