#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_8__ {scalar_t__ vmcs; } ;
struct TYPE_5__ {scalar_t__ base; } ;
struct TYPE_6__ {TYPE_1__ vmcs; } ;
struct TYPE_7__ {TYPE_2__ variant; } ;
struct pt_insn_decoder {TYPE_4__ asid; int /*<<< orphan*/  scache; TYPE_3__ event; } ;

/* Variables and functions */
 int pt_msec_cache_invalidate (int /*<<< orphan*/ *) ; 
 int pte_internal ; 

__attribute__((used)) static int pt_insn_process_vmcs(struct pt_insn_decoder *decoder)
{
	uint64_t vmcs;
	int errcode;

	if (!decoder)
		return -pte_internal;

	vmcs = decoder->event.variant.vmcs.base;
	if (decoder->asid.vmcs != vmcs) {
		errcode = pt_msec_cache_invalidate(&decoder->scache);
		if (errcode < 0)
			return errcode;

		decoder->asid.vmcs = vmcs;
	}

	return 0;
}