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
typedef  int /*<<< orphan*/  git_indexer_progress ;
struct TYPE_3__ {int /*<<< orphan*/  progress_payload; int /*<<< orphan*/  (* progress_cb ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ git_indexer ;

/* Variables and functions */
 int git_error_set_after_callback_function (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_progress_callback(git_indexer *idx, git_indexer_progress *stats)
{
	if (idx->progress_cb)
		return git_error_set_after_callback_function(
			idx->progress_cb(stats, idx->progress_payload),
			"indexer progress");
	return 0;
}