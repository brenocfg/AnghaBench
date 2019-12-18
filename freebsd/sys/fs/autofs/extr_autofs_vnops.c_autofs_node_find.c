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
struct autofs_node {int /*<<< orphan*/  an_name; int /*<<< orphan*/  an_children; int /*<<< orphan*/  an_mount; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTOFS_ASSERT_LOCKED (int /*<<< orphan*/ ) ; 
 int ENOENT ; 
 int /*<<< orphan*/  M_AUTOFS ; 
 struct autofs_node* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct autofs_node*) ; 
 int /*<<< orphan*/  autofs_node_tree ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strndup (char const*,int,int /*<<< orphan*/ ) ; 

int
autofs_node_find(struct autofs_node *parent, const char *name,
    int namelen, struct autofs_node **anpp)
{
	struct autofs_node *anp, find;
	int error;

	AUTOFS_ASSERT_LOCKED(parent->an_mount);

	if (namelen >= 0)
		find.an_name = strndup(name, namelen, M_AUTOFS);
	else
		find.an_name = strdup(name, M_AUTOFS);

	anp = RB_FIND(autofs_node_tree, &parent->an_children, &find);
	if (anp != NULL) {
		error = 0;
		if (anpp != NULL)
			*anpp = anp;
	} else {
		error = ENOENT;
	}

	free(find.an_name, M_AUTOFS);

	return (error);
}