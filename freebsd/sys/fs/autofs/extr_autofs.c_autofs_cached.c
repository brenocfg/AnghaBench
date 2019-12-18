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
struct autofs_node {int an_cached; scalar_t__ an_wildcards; int /*<<< orphan*/ * an_parent; struct autofs_mount* an_mount; } ;
struct autofs_mount {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTOFS_ASSERT_UNLOCKED (struct autofs_mount*) ; 
 int /*<<< orphan*/  AUTOFS_SLOCK (struct autofs_mount*) ; 
 int /*<<< orphan*/  AUTOFS_SUNLOCK (struct autofs_mount*) ; 
 int autofs_node_find (struct autofs_node*,char const*,int,int /*<<< orphan*/ *) ; 

bool
autofs_cached(struct autofs_node *anp, const char *component, int componentlen)
{
	int error;
	struct autofs_mount *amp;

	amp = anp->an_mount;

	AUTOFS_ASSERT_UNLOCKED(amp);

	/*
	 * For root node we need to request automountd(8) assistance even
	 * if the node is marked as cached, but the requested top-level
	 * directory does not exist.  This is necessary for wildcard indirect
	 * map keys to work.  We don't do this if we know that there are
	 * no wildcards.
	 */
	if (anp->an_parent == NULL && componentlen != 0 && anp->an_wildcards) {
		AUTOFS_SLOCK(amp);
		error = autofs_node_find(anp, component, componentlen, NULL);
		AUTOFS_SUNLOCK(amp);
		if (error != 0)
			return (false);
	}

	return (anp->an_cached);
}