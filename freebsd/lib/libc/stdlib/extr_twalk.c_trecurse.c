#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct TYPE_9__* rlink; struct TYPE_9__* llink; } ;
typedef  TYPE_1__ posix_tnode ;
typedef  int /*<<< orphan*/  (* cmp_fn_t ) (TYPE_1__ const*,int /*<<< orphan*/ ,int) ;

/* Variables and functions */
 int /*<<< orphan*/  endorder ; 
 int /*<<< orphan*/  leaf ; 
 int /*<<< orphan*/  postorder ; 
 int /*<<< orphan*/  preorder ; 
 int /*<<< orphan*/  stub1 (TYPE_1__ const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__ const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__ const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_1__ const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
trecurse(const posix_tnode *root, cmp_fn_t action, int level)
{

	if (root->llink == NULL && root->rlink == NULL)
		(*action)(root, leaf, level);
	else {
		(*action)(root, preorder, level);
		if (root->llink != NULL)
			trecurse(root->llink, action, level + 1);
		(*action)(root, postorder, level);
		if (root->rlink != NULL)
			trecurse(root->rlink, action, level + 1);
		(*action)(root, endorder, level);
	}
}