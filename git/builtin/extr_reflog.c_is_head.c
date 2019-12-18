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

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,char const*) ; 
#define  REF_TYPE_MAIN_PSEUDOREF 129 
#define  REF_TYPE_OTHER_PSEUDOREF 128 
 int /*<<< orphan*/  parse_worktree_ref (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**) ; 
 int ref_type (char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int is_head(const char *refname)
{
	switch (ref_type(refname)) {
	case REF_TYPE_OTHER_PSEUDOREF:
	case REF_TYPE_MAIN_PSEUDOREF:
		if (parse_worktree_ref(refname, NULL, NULL, &refname))
			BUG("not a worktree ref: %s", refname);
		break;
	default:
		break;
	}
	return !strcmp(refname, "HEAD");
}