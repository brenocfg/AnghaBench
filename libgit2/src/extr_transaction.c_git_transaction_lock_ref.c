#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  payload; struct TYPE_9__* name; } ;
typedef  TYPE_1__ transaction_node ;
struct TYPE_10__ {int /*<<< orphan*/  db; int /*<<< orphan*/  locks; int /*<<< orphan*/  pool; } ;
typedef  TYPE_2__ git_transaction ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* git_pool_mallocz (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* git_pool_strdup (int /*<<< orphan*/ *,char const*) ; 
 int git_refdb_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_refdb_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_strmap_set (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 

int git_transaction_lock_ref(git_transaction *tx, const char *refname)
{
	int error;
	transaction_node *node;

	assert(tx && refname);

	node = git_pool_mallocz(&tx->pool, sizeof(transaction_node));
	GIT_ERROR_CHECK_ALLOC(node);

	node->name = git_pool_strdup(&tx->pool, refname);
	GIT_ERROR_CHECK_ALLOC(node->name);

	if ((error = git_refdb_lock(&node->payload, tx->db, refname)) < 0)
		return error;

	if ((error = git_strmap_set(tx->locks, node->name, node)) < 0)
		goto cleanup;

	return 0;

cleanup:
	git_refdb_unlock(tx->db, node->payload, false, false, NULL, NULL, NULL);

	return error;
}