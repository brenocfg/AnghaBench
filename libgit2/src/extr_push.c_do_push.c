#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int (* push ) (TYPE_3__*,TYPE_5__*,TYPE_4__ const*) ;} ;
typedef  TYPE_3__ git_transport ;
struct TYPE_16__ {int (* push_negotiation ) (int /*<<< orphan*/  const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  payload; scalar_t__ pack_progress; } ;
typedef  TYPE_4__ git_remote_callbacks ;
typedef  int /*<<< orphan*/  git_push_update ;
struct TYPE_14__ {int /*<<< orphan*/  length; scalar_t__ contents; } ;
struct TYPE_17__ {int /*<<< orphan*/  pb; TYPE_2__ updates; int /*<<< orphan*/  pb_parallelism; int /*<<< orphan*/  repo; TYPE_1__* remote; } ;
typedef  TYPE_5__ git_push ;
struct TYPE_13__ {TYPE_3__* transport; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_NET ; 
 int calculate_work (TYPE_5__*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_packbuilder_free (int /*<<< orphan*/ ) ; 
 int git_packbuilder_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_packbuilder_set_callbacks (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_packbuilder_set_threads (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int queue_objects (TYPE_5__*) ; 
 int stub1 (int /*<<< orphan*/  const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (TYPE_3__*,TYPE_5__*,TYPE_4__ const*) ; 

__attribute__((used)) static int do_push(git_push *push, const git_remote_callbacks *callbacks)
{
	int error = 0;
	git_transport *transport = push->remote->transport;

	if (!transport->push) {
		git_error_set(GIT_ERROR_NET, "remote transport doesn't support push");
		error = -1;
		goto on_error;
	}

	/*
	 * A pack-file MUST be sent if either create or update command
	 * is used, even if the server already has all the necessary
	 * objects.  In this case the client MUST send an empty pack-file.
	 */

	if ((error = git_packbuilder_new(&push->pb, push->repo)) < 0)
		goto on_error;

	git_packbuilder_set_threads(push->pb, push->pb_parallelism);

	if (callbacks && callbacks->pack_progress)
		if ((error = git_packbuilder_set_callbacks(push->pb, callbacks->pack_progress, callbacks->payload)) < 0)
			goto on_error;

	if ((error = calculate_work(push)) < 0)
		goto on_error;

	if (callbacks && callbacks->push_negotiation &&
	    (error = callbacks->push_negotiation((const git_push_update **) push->updates.contents,
					  push->updates.length, callbacks->payload)) < 0)
	    goto on_error;

	if ((error = queue_objects(push)) < 0 ||
	    (error = transport->push(transport, push, callbacks)) < 0)
		goto on_error;

on_error:
	git_packbuilder_free(push->pb);
	return error;
}