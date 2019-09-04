#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  repo; } ;
typedef  TYPE_1__ git_remote ;
struct TYPE_9__ {int report_status; int pb_parallelism; int /*<<< orphan*/  specs; int /*<<< orphan*/  status; int /*<<< orphan*/  updates; TYPE_1__* remote; int /*<<< orphan*/  repo; } ;
typedef  TYPE_2__ git_push ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_2__*) ; 
 TYPE_2__* git__calloc (int,int) ; 
 int /*<<< orphan*/  git__free (TYPE_2__*) ; 
 int /*<<< orphan*/  git_vector_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_vector_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * push_spec_rref_cmp ; 
 int /*<<< orphan*/ * push_status_ref_cmp ; 

int git_push_new(git_push **out, git_remote *remote)
{
	git_push *p;

	*out = NULL;

	p = git__calloc(1, sizeof(*p));
	GIT_ERROR_CHECK_ALLOC(p);

	p->repo = remote->repo;
	p->remote = remote;
	p->report_status = 1;
	p->pb_parallelism = 1;

	if (git_vector_init(&p->specs, 0, push_spec_rref_cmp) < 0) {
		git__free(p);
		return -1;
	}

	if (git_vector_init(&p->status, 0, push_status_ref_cmp) < 0) {
		git_vector_free(&p->specs);
		git__free(p);
		return -1;
	}

	if (git_vector_init(&p->updates, 0, NULL) < 0) {
		git_vector_free(&p->status);
		git_vector_free(&p->specs);
		git__free(p);
		return -1;
	}

	*out = p;
	return 0;
}