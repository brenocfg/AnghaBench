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
struct TYPE_4__ {int (* push_transfer_progress ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  payload; } ;
typedef  TYPE_1__ git_remote_callbacks ;
struct TYPE_5__ {int /*<<< orphan*/  received_bytes; int /*<<< orphan*/  total_objects; int /*<<< orphan*/  received_objects; } ;
typedef  TYPE_2__ git_indexer_progress ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int transfer_to_push_transfer(const git_indexer_progress *stats, void *payload)
{
	const git_remote_callbacks *cbs = payload;

	if (!cbs || !cbs->push_transfer_progress)
		return 0;

	return cbs->push_transfer_progress(stats->received_objects, stats->total_objects, stats->received_bytes,
					   cbs->payload);
}