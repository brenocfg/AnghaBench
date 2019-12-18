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
struct TYPE_3__ {int mode; } ;
struct TYPE_4__ {TYPE_1__ exec_mode; } ;
struct pt_event {scalar_t__ status_update; TYPE_2__ variant; } ;
struct pt_block_decoder {scalar_t__ mode; scalar_t__ process_event; scalar_t__ enabled; } ;
typedef  enum pt_exec_mode { ____Placeholder_pt_exec_mode } pt_exec_mode ;

/* Variables and functions */
 int pte_bad_status_update ; 
 int pte_internal ; 
 scalar_t__ ptem_unknown ; 

__attribute__((used)) static int pt_blk_process_exec_mode(struct pt_block_decoder *decoder,
				    const struct pt_event *ev)
{
	enum pt_exec_mode mode;

	if (!decoder || !ev)
		return -pte_internal;

	/* Use status update events to diagnose inconsistencies. */
	mode = ev->variant.exec_mode.mode;
	if (ev->status_update && decoder->enabled &&
	    decoder->mode != ptem_unknown && decoder->mode != mode)
		return -pte_bad_status_update;

	decoder->mode = mode;
	decoder->process_event = 0;

	return 0;
}