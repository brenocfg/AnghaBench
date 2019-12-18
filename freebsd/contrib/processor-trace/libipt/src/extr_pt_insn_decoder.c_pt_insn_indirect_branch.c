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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {scalar_t__ enable_tick_events; } ;
struct TYPE_5__ {TYPE_1__ insn; } ;
struct TYPE_6__ {TYPE_2__ variant; } ;
struct pt_insn_decoder {TYPE_3__ flags; int /*<<< orphan*/  query; int /*<<< orphan*/  ip; } ;

/* Variables and functions */
 int pt_insn_tick (struct pt_insn_decoder*,int /*<<< orphan*/ ) ; 
 int pt_qry_indirect_branch (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pte_internal ; 

__attribute__((used)) static int pt_insn_indirect_branch(struct pt_insn_decoder *decoder,
				   uint64_t *ip)
{
	uint64_t evip;
	int status, errcode;

	if (!decoder)
		return -pte_internal;

	evip = decoder->ip;

	status = pt_qry_indirect_branch(&decoder->query, ip);
	if (status < 0)
		return status;

	if (decoder->flags.variant.insn.enable_tick_events) {
		errcode = pt_insn_tick(decoder, evip);
		if (errcode < 0)
			return errcode;
	}

	return status;
}