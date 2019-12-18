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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  miss (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtree_readspec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path ; 
 int /*<<< orphan*/  root ; 
 int vwalk () ; 

int
mtree_verifyspec(FILE *fi)
{
	int rval;

	root = mtree_readspec(fi);
	rval = vwalk();
	miss(root, path);
	return (rval);
}