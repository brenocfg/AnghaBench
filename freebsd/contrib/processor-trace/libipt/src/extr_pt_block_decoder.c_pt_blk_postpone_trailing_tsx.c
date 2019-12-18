#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ ip; } ;
struct TYPE_10__ {TYPE_4__ tsx; } ;
struct pt_event {TYPE_5__ variant; scalar_t__ ip_suppressed; } ;
struct TYPE_6__ {scalar_t__ bdm64; } ;
struct TYPE_7__ {TYPE_1__ errata; } ;
struct TYPE_8__ {TYPE_2__ config; } ;
struct pt_block_decoder {scalar_t__ ip; TYPE_3__ query; } ;
struct pt_block {int dummy; } ;

/* Variables and functions */
 int pt_blk_handle_erratum_bdm64 (struct pt_block_decoder*,struct pt_block*,struct pt_event const*) ; 
 int pte_internal ; 

__attribute__((used)) static inline int pt_blk_postpone_trailing_tsx(struct pt_block_decoder *decoder,
					       struct pt_block *block,
					       const struct pt_event *ev)
{
	int status;

	if (!decoder || !ev)
		return -pte_internal;

	if (ev->ip_suppressed)
		return 0;

	if (block && decoder->query.config.errata.bdm64) {
		status = pt_blk_handle_erratum_bdm64(decoder, block, ev);
		if (status < 0)
			return 1;
	}

	if (decoder->ip != ev->variant.tsx.ip)
		return 1;

	return 0;
}