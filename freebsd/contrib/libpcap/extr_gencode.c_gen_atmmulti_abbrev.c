#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct block {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  is_atm; } ;
typedef  TYPE_1__ compiler_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  A_CALLPROCEED ; 
 int /*<<< orphan*/  A_CONNECT ; 
 int /*<<< orphan*/  A_CONNECTACK ; 
#define  A_CONNECTMSG 131 
 int /*<<< orphan*/  A_METAC ; 
#define  A_METACONNECT 130 
#define  A_OAM 129 
#define  A_OAMF4 128 
 int /*<<< orphan*/  A_RELEASE ; 
 int /*<<< orphan*/  A_RELEASE_DONE ; 
 int /*<<< orphan*/  A_SC ; 
 int /*<<< orphan*/  A_SETUP ; 
 int /*<<< orphan*/  A_VCI ; 
 int /*<<< orphan*/  A_VPI ; 
 int /*<<< orphan*/  BPF_JEQ ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  bpf_error (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  gen_and (struct block*,struct block*) ; 
 struct block* gen_atmfield_code (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct block* gen_atmtype_abbrev (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct block* gen_msg_abbrev (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_or (struct block*,struct block*) ; 

struct block *
gen_atmmulti_abbrev(compiler_state_t *cstate, int type)
{
	struct block *b0, *b1;

	switch (type) {

	case A_OAM:
		if (!cstate->is_atm)
			bpf_error(cstate, "'oam' supported only on raw ATM");
		b1 = gen_atmmulti_abbrev(cstate, A_OAMF4);
		break;

	case A_OAMF4:
		if (!cstate->is_atm)
			bpf_error(cstate, "'oamf4' supported only on raw ATM");
		/* OAM F4 type */
		b0 = gen_atmfield_code(cstate, A_VCI, 3, BPF_JEQ, 0);
		b1 = gen_atmfield_code(cstate, A_VCI, 4, BPF_JEQ, 0);
		gen_or(b0, b1);
		b0 = gen_atmfield_code(cstate, A_VPI, 0, BPF_JEQ, 0);
		gen_and(b0, b1);
		break;

	case A_CONNECTMSG:
		/*
		 * Get Q.2931 signalling messages for switched
		 * virtual connection
		 */
		if (!cstate->is_atm)
			bpf_error(cstate, "'connectmsg' supported only on raw ATM");
		b0 = gen_msg_abbrev(cstate, A_SETUP);
		b1 = gen_msg_abbrev(cstate, A_CALLPROCEED);
		gen_or(b0, b1);
		b0 = gen_msg_abbrev(cstate, A_CONNECT);
		gen_or(b0, b1);
		b0 = gen_msg_abbrev(cstate, A_CONNECTACK);
		gen_or(b0, b1);
		b0 = gen_msg_abbrev(cstate, A_RELEASE);
		gen_or(b0, b1);
		b0 = gen_msg_abbrev(cstate, A_RELEASE_DONE);
		gen_or(b0, b1);
		b0 = gen_atmtype_abbrev(cstate, A_SC);
		gen_and(b0, b1);
		break;

	case A_METACONNECT:
		if (!cstate->is_atm)
			bpf_error(cstate, "'metaconnect' supported only on raw ATM");
		b0 = gen_msg_abbrev(cstate, A_SETUP);
		b1 = gen_msg_abbrev(cstate, A_CALLPROCEED);
		gen_or(b0, b1);
		b0 = gen_msg_abbrev(cstate, A_CONNECT);
		gen_or(b0, b1);
		b0 = gen_msg_abbrev(cstate, A_RELEASE);
		gen_or(b0, b1);
		b0 = gen_msg_abbrev(cstate, A_RELEASE_DONE);
		gen_or(b0, b1);
		b0 = gen_atmtype_abbrev(cstate, A_METAC);
		gen_and(b0, b1);
		break;

	default:
		abort();
	}
	return b1;
}