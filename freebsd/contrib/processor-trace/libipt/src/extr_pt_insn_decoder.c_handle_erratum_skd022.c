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
struct TYPE_5__ {int /*<<< orphan*/  ip; } ;
struct TYPE_4__ {int /*<<< orphan*/  ip; } ;
struct TYPE_6__ {TYPE_2__ disabled; TYPE_1__ async_disabled; } ;
struct pt_event {TYPE_3__ variant; int /*<<< orphan*/  type; } ;
struct pt_insn_decoder {struct pt_event event; } ;

/* Variables and functions */
 int check_erratum_skd022 (struct pt_insn_decoder*) ; 
 int pte_internal ; 
 int /*<<< orphan*/  ptev_disabled ; 

__attribute__((used)) static inline int handle_erratum_skd022(struct pt_insn_decoder *decoder)
{
	struct pt_event *ev;
	uint64_t ip;
	int errcode;

	if (!decoder)
		return -pte_internal;

	errcode = check_erratum_skd022(decoder);
	if (errcode <= 0)
		return errcode;

	/* We turn the async disable into a sync disable.  It will be processed
	 * after decoding the instruction.
	 */
	ev = &decoder->event;

	ip = ev->variant.async_disabled.ip;

	ev->type = ptev_disabled;
	ev->variant.disabled.ip = ip;

	return 1;
}