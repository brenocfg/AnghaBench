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
struct TYPE_5__ {int /*<<< orphan*/  message; int /*<<< orphan*/  sig; } ;
typedef  TYPE_1__ transaction_node ;
struct TYPE_6__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  repo; } ;
typedef  TYPE_2__ git_transaction ;
typedef  int /*<<< orphan*/  const git_signature ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_pool_strdup (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ git_reference__log_signature (int /*<<< orphan*/  const**,int /*<<< orphan*/ ) ; 
 scalar_t__ git_signature__pdup (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature_free (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int copy_common(transaction_node *node, git_transaction *tx, const git_signature *sig, const char *msg)
{
	if (sig && git_signature__pdup(&node->sig, sig, &tx->pool) < 0)
		return -1;

	if (!node->sig) {
		git_signature *tmp;
		int error;

		if (git_reference__log_signature(&tmp, tx->repo) < 0)
			return -1;

		/* make sure the sig we use is in our pool */
		error = git_signature__pdup(&node->sig, tmp, &tx->pool);
		git_signature_free(tmp);
		if (error < 0)
			return error;
	}

	if (msg) {
		node->message = git_pool_strdup(&tx->pool, msg);
		GIT_ERROR_CHECK_ALLOC(node->message);
	}

	return 0;
}