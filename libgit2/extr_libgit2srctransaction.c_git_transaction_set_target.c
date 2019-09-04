#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {int /*<<< orphan*/  ref_type; TYPE_1__ target; } ;
typedef  TYPE_2__ transaction_node ;
typedef  int /*<<< orphan*/  git_transaction ;
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REFERENCE_DIRECT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int copy_common (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char const*) ; 
 int find_locked (TYPE_2__**,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

int git_transaction_set_target(git_transaction *tx, const char *refname, const git_oid *target, const git_signature *sig, const char *msg)
{
	int error;
	transaction_node *node;

	assert(tx && refname && target);

	if ((error = find_locked(&node, tx, refname)) < 0)
		return error;

	if ((error = copy_common(node, tx, sig, msg)) < 0)
		return error;

	git_oid_cpy(&node->target.id, target);
	node->ref_type = GIT_REFERENCE_DIRECT;

	return 0;
}