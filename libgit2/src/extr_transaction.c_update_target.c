#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  symbolic; int /*<<< orphan*/  id; } ;
struct TYPE_5__ {scalar_t__ ref_type; int committed; int /*<<< orphan*/ * message; int /*<<< orphan*/ * sig; int /*<<< orphan*/  payload; scalar_t__ remove; int /*<<< orphan*/ * reflog; TYPE_1__ target; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ transaction_node ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_refdb ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (int /*<<< orphan*/ *) ; 
 scalar_t__ GIT_REFERENCE_DIRECT ; 
 scalar_t__ GIT_REFERENCE_SYMBOLIC ; 
 int /*<<< orphan*/  abort () ; 
 int git_refdb_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_reference__alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_reference__alloc_symbolic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int update_target(git_refdb *db, transaction_node *node)
{
	git_reference *ref;
	int error, update_reflog;

	if (node->ref_type == GIT_REFERENCE_DIRECT) {
		ref = git_reference__alloc(node->name, &node->target.id, NULL);
	} else if (node->ref_type == GIT_REFERENCE_SYMBOLIC) {
		ref = git_reference__alloc_symbolic(node->name, node->target.symbolic);
	} else {
		abort();
	}

	GIT_ERROR_CHECK_ALLOC(ref);
	update_reflog = node->reflog == NULL;

	if (node->remove) {
		error =  git_refdb_unlock(db, node->payload, 2, false, ref, NULL, NULL);
	} else if (node->ref_type == GIT_REFERENCE_DIRECT) {
		error = git_refdb_unlock(db, node->payload, true, update_reflog, ref, node->sig, node->message);
	} else if (node->ref_type == GIT_REFERENCE_SYMBOLIC) {
		error = git_refdb_unlock(db, node->payload, true, update_reflog, ref, node->sig, node->message);
	} else {
		abort();
	}

	git_reference_free(ref);
	node->committed = true;

	return error;
}