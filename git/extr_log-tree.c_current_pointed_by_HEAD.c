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
struct name_decoration {scalar_t__ type; int /*<<< orphan*/  name; struct name_decoration* next; } ;

/* Variables and functions */
 scalar_t__ DECORATION_REF_HEAD ; 
 scalar_t__ DECORATION_REF_LOCAL ; 
 int REF_ISSYMREF ; 
 char* resolve_ref_unsafe (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  starts_with (char const*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct name_decoration *current_pointed_by_HEAD(const struct name_decoration *decoration)
{
	const struct name_decoration *list, *head = NULL;
	const char *branch_name = NULL;
	int rru_flags;

	/* First find HEAD */
	for (list = decoration; list; list = list->next)
		if (list->type == DECORATION_REF_HEAD) {
			head = list;
			break;
		}
	if (!head)
		return NULL;

	/* Now resolve and find the matching current branch */
	branch_name = resolve_ref_unsafe("HEAD", 0, NULL, &rru_flags);
	if (!branch_name || !(rru_flags & REF_ISSYMREF))
		return NULL;

	if (!starts_with(branch_name, "refs/"))
		return NULL;

	/* OK, do we have that ref in the list? */
	for (list = decoration; list; list = list->next)
		if ((list->type == DECORATION_REF_LOCAL) &&
		    !strcmp(branch_name, list->name)) {
			return list;
		}

	return NULL;
}