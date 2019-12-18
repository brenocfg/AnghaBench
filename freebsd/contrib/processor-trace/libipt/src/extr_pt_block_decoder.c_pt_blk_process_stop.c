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
struct pt_event {scalar_t__ status_update; } ;
struct pt_block_decoder {scalar_t__ process_event; scalar_t__ enabled; } ;

/* Variables and functions */
 int pte_bad_context ; 
 int pte_internal ; 

__attribute__((used)) static int pt_blk_process_stop(struct pt_block_decoder *decoder,
			       const struct pt_event *ev)
{
	if (!decoder || !ev)
		return -pte_internal;

	/* This event can't be a status update. */
	if (ev->status_update)
		return -pte_bad_context;

	/* Tracing is always disabled before it is stopped. */
	if (decoder->enabled)
		return -pte_bad_context;

	decoder->process_event = 0;

	return 0;
}