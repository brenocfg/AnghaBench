#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct block {int dummy; } ;
struct TYPE_5__ {scalar_t__ off_proto; int /*<<< orphan*/  is_atm; scalar_t__ off_payload; scalar_t__ off_vci; scalar_t__ off_vpi; } ;
typedef  TYPE_1__ compiler_state_t ;
typedef  int /*<<< orphan*/  bpf_u_int32 ;
typedef  int /*<<< orphan*/  bpf_int32 ;

/* Variables and functions */
#define  A_CALLREFTYPE 132 
#define  A_MSGTYPE 131 
#define  A_PROTOTYPE 130 
#define  A_VCI 129 
#define  A_VPI 128 
 int /*<<< orphan*/  BPF_B ; 
 int /*<<< orphan*/  BPF_H ; 
 scalar_t__ MSG_TYPE_POS ; 
 scalar_t__ OFFSET_NOT_SET ; 
 int /*<<< orphan*/  OR_LINKHDR ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  bpf_error (TYPE_1__*,char*) ; 
 struct block* gen_ncmp (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

struct block *
gen_atmfield_code(compiler_state_t *cstate, int atmfield, bpf_int32 jvalue,
    bpf_u_int32 jtype, int reverse)
{
	struct block *b0;

	switch (atmfield) {

	case A_VPI:
		if (!cstate->is_atm)
			bpf_error(cstate, "'vpi' supported only on raw ATM");
		if (cstate->off_vpi == OFFSET_NOT_SET)
			abort();
		b0 = gen_ncmp(cstate, OR_LINKHDR, cstate->off_vpi, BPF_B, 0xffffffff, jtype,
		    reverse, jvalue);
		break;

	case A_VCI:
		if (!cstate->is_atm)
			bpf_error(cstate, "'vci' supported only on raw ATM");
		if (cstate->off_vci == OFFSET_NOT_SET)
			abort();
		b0 = gen_ncmp(cstate, OR_LINKHDR, cstate->off_vci, BPF_H, 0xffffffff, jtype,
		    reverse, jvalue);
		break;

	case A_PROTOTYPE:
		if (cstate->off_proto == OFFSET_NOT_SET)
			abort();	/* XXX - this isn't on FreeBSD */
		b0 = gen_ncmp(cstate, OR_LINKHDR, cstate->off_proto, BPF_B, 0x0f, jtype,
		    reverse, jvalue);
		break;

	case A_MSGTYPE:
		if (cstate->off_payload == OFFSET_NOT_SET)
			abort();
		b0 = gen_ncmp(cstate, OR_LINKHDR, cstate->off_payload + MSG_TYPE_POS, BPF_B,
		    0xffffffff, jtype, reverse, jvalue);
		break;

	case A_CALLREFTYPE:
		if (!cstate->is_atm)
			bpf_error(cstate, "'callref' supported only on raw ATM");
		if (cstate->off_proto == OFFSET_NOT_SET)
			abort();
		b0 = gen_ncmp(cstate, OR_LINKHDR, cstate->off_proto, BPF_B, 0xffffffff,
		    jtype, reverse, jvalue);
		break;

	default:
		abort();
	}
	return b0;
}