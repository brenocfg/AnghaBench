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
struct TYPE_8__ {int (* negotiate_fetch ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const* const*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ git_transport ;
typedef  int /*<<< orphan*/  git_remote_head ;
struct TYPE_7__ {int /*<<< orphan*/  length; scalar_t__ contents; } ;
struct TYPE_9__ {TYPE_1__ refs; int /*<<< orphan*/  repo; scalar_t__ need_pack; TYPE_2__* transport; } ;
typedef  TYPE_3__ git_remote ;
typedef  int /*<<< orphan*/  git_fetch_options ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_NET ; 
 scalar_t__ filter_wants (TYPE_3__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/  const* const*,int /*<<< orphan*/ ) ; 

int git_fetch_negotiate(git_remote *remote, const git_fetch_options *opts)
{
	git_transport *t = remote->transport;

	remote->need_pack = 0;

	if (filter_wants(remote, opts) < 0) {
		git_error_set(GIT_ERROR_NET, "failed to filter the reference list for wants");
		return -1;
	}

	/* Don't try to negotiate when we don't want anything */
	if (!remote->need_pack)
		return 0;

	/*
	 * Now we have everything set up so we can start tell the
	 * server what we want and what we have.
	 */
	return t->negotiate_fetch(t,
		remote->repo,
		(const git_remote_head * const *)remote->refs.contents,
		remote->refs.length);
}