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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int /*<<< orphan*/  displacement; int /*<<< orphan*/  is_direct; } ;
struct TYPE_4__ {TYPE_1__ branch; } ;
struct pt_insn_ext {TYPE_2__ variant; } ;
struct pt_insn {int iclass; int /*<<< orphan*/  size; int /*<<< orphan*/  ip; } ;
struct pt_event {int /*<<< orphan*/  ip_suppressed; } ;
struct pt_config {int /*<<< orphan*/  addr_filter; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int pt_filter_addr_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pte_internal ; 
#define  ptic_call 129 
#define  ptic_jump 128 

__attribute__((used)) static int pt_insn_at_skl014(const struct pt_event *ev,
			     const struct pt_insn *insn,
			     const struct pt_insn_ext *iext,
			     const struct pt_config *config)
{
	uint64_t ip;
	int status;

	if (!ev || !insn || !iext || !config)
		return -pte_internal;

	if (!ev->ip_suppressed)
		return 0;

	switch (insn->iclass) {
	case ptic_call:
	case ptic_jump:
		/* The erratum only applies to unconditional direct branches. */
		if (!iext->variant.branch.is_direct)
			break;

		/* Check the filter against the branch target. */
		ip = insn->ip;
		ip += insn->size;
		ip += (uint64_t) (int64_t) iext->variant.branch.displacement;

		status = pt_filter_addr_check(&config->addr_filter, ip);
		if (status <= 0) {
			if (status < 0)
				return status;

			return 1;
		}
		break;

	default:
		break;
	}

	return 0;
}