#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  to; } ;
struct TYPE_4__ {TYPE_1__ async_branch; } ;
struct pt_event {TYPE_2__ variant; scalar_t__ status_update; } ;
struct pt_block_decoder {scalar_t__ process_event; int /*<<< orphan*/  ip; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int pte_bad_context ; 
 int pte_internal ; 

__attribute__((used)) static int pt_blk_process_async_branch(struct pt_block_decoder *decoder,
				       const struct pt_event *ev)
{
	if (!decoder || !ev)
		return -pte_internal;

	/* This event can't be a status update. */
	if (ev->status_update)
		return -pte_bad_context;

	/* We must currently be enabled. */
	if (!decoder->enabled)
		return -pte_bad_context;

	/* Jump to the branch destination.  We will continue from there in the
	 * next iteration.
	 */
	decoder->ip = ev->variant.async_branch.to;
	decoder->process_event = 0;

	return 0;
}