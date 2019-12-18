#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ git_revwalk_hide_cb ;
struct TYPE_5__ {int limited; void* hide_cb_payload; scalar_t__ hide_cb; scalar_t__ walking; } ;
typedef  TYPE_1__ git_revwalk ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  git_revwalk_reset (TYPE_1__*) ; 

int git_revwalk_add_hide_cb(
	git_revwalk *walk,
	git_revwalk_hide_cb hide_cb,
	void *payload)
{
	assert(walk);

	if (walk->walking)
		git_revwalk_reset(walk);

	walk->hide_cb = hide_cb;
	walk->hide_cb_payload = payload;

	if (hide_cb)
		walk->limited = 1;

	return 0;
}