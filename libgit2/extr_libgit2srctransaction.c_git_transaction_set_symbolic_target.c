#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  symbolic; } ;
struct TYPE_10__ {int /*<<< orphan*/  ref_type; TYPE_1__ target; } ;
typedef  TYPE_2__ transaction_node ;
struct TYPE_11__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ git_transaction ;
typedef  int /*<<< orphan*/  git_signature ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GIT_REFERENCE_SYMBOLIC ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int copy_common (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/  const*,char const*) ; 
 int find_locked (TYPE_2__**,TYPE_3__*,char const*) ; 
 int /*<<< orphan*/  git_pool_strdup (int /*<<< orphan*/ *,char const*) ; 

int git_transaction_set_symbolic_target(git_transaction *tx, const char *refname, const char *target, const git_signature *sig, const char *msg)
{
	int error;
	transaction_node *node;

	assert(tx && refname && target);

	if ((error = find_locked(&node, tx, refname)) < 0)
		return error;

	if ((error = copy_common(node, tx, sig, msg)) < 0)
		return error;

	node->target.symbolic = git_pool_strdup(&tx->pool, target);
	GIT_ERROR_CHECK_ALLOC(node->target.symbolic);
	node->ref_type = GIT_REFERENCE_SYMBOLIC;

	return 0;
}