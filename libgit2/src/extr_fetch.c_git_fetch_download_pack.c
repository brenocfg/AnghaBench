#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int (* download_pack ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ;} ;
typedef  TYPE_1__ git_transport ;
struct TYPE_8__ {void* payload; int /*<<< orphan*/ * transfer_progress; } ;
typedef  TYPE_2__ git_remote_callbacks ;
struct TYPE_9__ {int /*<<< orphan*/  stats; int /*<<< orphan*/  repo; int /*<<< orphan*/  need_pack; TYPE_1__* transport; } ;
typedef  TYPE_3__ git_remote ;
typedef  int /*<<< orphan*/ * git_indexer_progress_cb ;

/* Variables and functions */
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 

int git_fetch_download_pack(git_remote *remote, const git_remote_callbacks *callbacks)
{
	git_transport *t = remote->transport;
	git_indexer_progress_cb progress = NULL;
	void *payload = NULL;

	if (!remote->need_pack)
		return 0;

	if (callbacks) {
		progress = callbacks->transfer_progress;
		payload  = callbacks->payload;
	}

	return t->download_pack(t, remote->repo, &remote->stats, progress, payload);
}