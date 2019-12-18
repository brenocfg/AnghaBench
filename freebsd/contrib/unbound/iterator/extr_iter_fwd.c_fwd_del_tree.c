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
struct iter_forwards {scalar_t__ tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  delfwdnode ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  traverse_postorder (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fwd_del_tree(struct iter_forwards* fwd)
{
	if(fwd->tree)
		traverse_postorder(fwd->tree, &delfwdnode, NULL);
	free(fwd->tree);
}