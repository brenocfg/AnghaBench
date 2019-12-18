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
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/  displacement; int /*<<< orphan*/  is_direct; } ;
struct TYPE_3__ {TYPE_2__ branch; } ;
struct pt_insn_ext {TYPE_1__ variant; } ;
struct pt_insn {int iclass; scalar_t__ size; scalar_t__ ip; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  fallthrough ; 
 int pte_bad_insn ; 
 int pte_bad_query ; 
 int pte_internal ; 
#define  ptic_call 132 
#define  ptic_error 131 
#define  ptic_jump 130 
#define  ptic_other 129 
#define  ptic_ptwrite 128 

int pt_insn_next_ip(uint64_t *pip, const struct pt_insn *insn,
		    const struct pt_insn_ext *iext)
{
	uint64_t ip;

	if (!insn || !iext)
		return -pte_internal;

	ip = insn->ip + insn->size;

	switch (insn->iclass) {
	case ptic_ptwrite:
	case ptic_other:
		break;

	case ptic_call:
	case ptic_jump:
		if (iext->variant.branch.is_direct) {
			ip += (uint64_t) (int64_t)
				iext->variant.branch.displacement;
			break;
		}

		fallthrough;
	default:
		return -pte_bad_query;

	case ptic_error:
		return -pte_bad_insn;
	}

	if (pip)
		*pip = ip;

	return 0;
}