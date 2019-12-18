#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int remove; int /*<<< orphan*/  ref_type; } ;
typedef  TYPE_1__ transaction_node ;
typedef  int /*<<< orphan*/  git_transaction ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REFERENCE_DIRECT ; 
 int find_locked (TYPE_1__**,int /*<<< orphan*/ *,char const*) ; 

int git_transaction_remove(git_transaction *tx, const char *refname)
{
	int error;
	transaction_node *node;

	if ((error = find_locked(&node, tx, refname)) < 0)
		return error;

	node->remove = true;
	node->ref_type = GIT_REFERENCE_DIRECT; /* the id will be ignored */

	return 0;
}