#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_packbuilder_progress ;
struct TYPE_3__ {void* progress_cb_payload; int /*<<< orphan*/  progress_cb; } ;
typedef  TYPE_1__ git_packbuilder ;

/* Variables and functions */

int git_packbuilder_set_callbacks(git_packbuilder *pb, git_packbuilder_progress progress_cb, void *progress_cb_payload)
{
	if (!pb)
		return -1;

	pb->progress_cb = progress_cb;
	pb->progress_cb_payload = progress_cb_payload;

	return 0;
}