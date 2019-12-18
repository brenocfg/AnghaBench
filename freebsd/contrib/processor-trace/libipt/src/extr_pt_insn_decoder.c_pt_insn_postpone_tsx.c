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
struct pt_insn_ext {int dummy; } ;
struct TYPE_8__ {scalar_t__ bdm64; } ;
struct TYPE_9__ {TYPE_3__ errata; } ;
struct TYPE_10__ {TYPE_4__ config; } ;
struct pt_insn_decoder {scalar_t__ ip; TYPE_5__ query; } ;
struct pt_insn {int dummy; } ;
struct TYPE_6__ {scalar_t__ ip; } ;
struct TYPE_7__ {TYPE_1__ tsx; } ;
struct pt_event {TYPE_2__ variant; scalar_t__ ip_suppressed; } ;

/* Variables and functions */
 int handle_erratum_bdm64 (struct pt_insn_decoder*,struct pt_event const*,struct pt_insn const*,struct pt_insn_ext const*) ; 
 int pte_internal ; 

__attribute__((used)) static inline int pt_insn_postpone_tsx(struct pt_insn_decoder *decoder,
				       const struct pt_insn *insn,
				       const struct pt_insn_ext *iext,
				       const struct pt_event *ev)
{
	int status;

	if (!decoder || !ev)
		return -pte_internal;

	if (ev->ip_suppressed)
		return 0;

	if (insn && iext && decoder->query.config.errata.bdm64) {
		status = handle_erratum_bdm64(decoder, ev, insn, iext);
		if (status < 0)
			return status;
	}

	if (decoder->ip != ev->variant.tsx.ip)
		return 1;

	return 0;
}