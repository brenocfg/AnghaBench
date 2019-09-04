#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  void git_indexer_progress ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (void*) ; 

__attribute__((used)) static int clone_cancel_fetch_transfer_progress_cb(
	const git_indexer_progress *stats, void *data)
{
	GIT_UNUSED(stats); GIT_UNUSED(data);
	return -54321;
}