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
typedef  int /*<<< orphan*/  NODE ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MISMATCHEXIT ; 
 scalar_t__ compare_nodes (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * spec (int /*<<< orphan*/ *) ; 
 int walk_in_the_forest (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

int
mtree_specspec(FILE *fi, FILE *fj)
{
	int rval;
	NODE *root1, *root2;

	root1 = spec(fi);
	root2 = spec(fj);
	rval = walk_in_the_forest(root1, root2, "");
	rval += compare_nodes(root1, root2, "");
	if (rval > 0)
		return (MISMATCHEXIT);
	return (0);
}