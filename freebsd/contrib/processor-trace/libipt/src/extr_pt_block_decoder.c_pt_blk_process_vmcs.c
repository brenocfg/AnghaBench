#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {scalar_t__ base; } ;
struct TYPE_5__ {TYPE_1__ vmcs; } ;
struct pt_event {TYPE_2__ variant; } ;
struct TYPE_6__ {scalar_t__ vmcs; } ;
struct pt_block_decoder {scalar_t__ process_event; TYPE_3__ asid; int /*<<< orphan*/  scache; } ;

/* Variables and functions */
 int pt_msec_cache_invalidate (int /*<<< orphan*/ *) ; 
 int pte_internal ; 

__attribute__((used)) static int pt_blk_process_vmcs(struct pt_block_decoder *decoder,
			       const struct pt_event *ev)
{
	uint64_t vmcs;
	int errcode;

	if (!decoder || !ev)
		return -pte_internal;

	vmcs = ev->variant.vmcs.base;
	if (decoder->asid.vmcs != vmcs) {
		errcode = pt_msec_cache_invalidate(&decoder->scache);
		if (errcode < 0)
			return errcode;

		decoder->asid.vmcs = vmcs;
	}

	decoder->process_event = 0;

	return 0;
}