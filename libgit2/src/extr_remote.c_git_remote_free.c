#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* name; struct TYPE_6__* pushurl; struct TYPE_6__* url; int /*<<< orphan*/  push; int /*<<< orphan*/  passive_refspecs; int /*<<< orphan*/  active_refspecs; int /*<<< orphan*/  refspecs; int /*<<< orphan*/  refs; TYPE_2__* transport; } ;
typedef  TYPE_1__ git_remote ;
struct TYPE_7__ {int /*<<< orphan*/  (* free ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free_refspecs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_push_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_remote_disconnect (TYPE_1__*) ; 
 int /*<<< orphan*/  git_vector_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void git_remote_free(git_remote *remote)
{
	if (remote == NULL)
		return;

	if (remote->transport != NULL) {
		git_remote_disconnect(remote);

		remote->transport->free(remote->transport);
		remote->transport = NULL;
	}

	git_vector_free(&remote->refs);

	free_refspecs(&remote->refspecs);
	git_vector_free(&remote->refspecs);

	free_refspecs(&remote->active_refspecs);
	git_vector_free(&remote->active_refspecs);

	free_refspecs(&remote->passive_refspecs);
	git_vector_free(&remote->passive_refspecs);

	git_push_free(remote->push);
	git__free(remote->url);
	git__free(remote->pushurl);
	git__free(remote->name);
	git__free(remote);
}