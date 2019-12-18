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
struct branch {int /*<<< orphan*/ * name; int /*<<< orphan*/  refname; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct branch**,int,int /*<<< orphan*/ ) ; 
 struct branch** branches ; 
 int /*<<< orphan*/  branches_alloc ; 
 int branches_nr ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncmp (char const*,int /*<<< orphan*/ *,int) ; 
 struct branch* xcalloc (int,int) ; 
 int /*<<< orphan*/ * xstrdup (char const*) ; 
 int /*<<< orphan*/  xstrfmt (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xstrndup (char const*,int) ; 

__attribute__((used)) static struct branch *make_branch(const char *name, int len)
{
	struct branch *ret;
	int i;

	for (i = 0; i < branches_nr; i++) {
		if (len ? (!strncmp(name, branches[i]->name, len) &&
			   !branches[i]->name[len]) :
		    !strcmp(name, branches[i]->name))
			return branches[i];
	}

	ALLOC_GROW(branches, branches_nr + 1, branches_alloc);
	ret = xcalloc(1, sizeof(struct branch));
	branches[branches_nr++] = ret;
	if (len)
		ret->name = xstrndup(name, len);
	else
		ret->name = xstrdup(name);
	ret->refname = xstrfmt("refs/heads/%s", ret->name);

	return ret;
}