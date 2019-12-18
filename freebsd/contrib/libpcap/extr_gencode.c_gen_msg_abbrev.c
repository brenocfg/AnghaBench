#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct block {int dummy; } ;
typedef  int /*<<< orphan*/  compiler_state_t ;

/* Variables and functions */
#define  A_CALLPROCEED 133 
#define  A_CONNECT 132 
#define  A_CONNECTACK 131 
 int /*<<< orphan*/  A_MSGTYPE ; 
#define  A_RELEASE 130 
#define  A_RELEASE_DONE 129 
#define  A_SETUP 128 
 int /*<<< orphan*/  BPF_JEQ ; 
 int /*<<< orphan*/  CALL_PROCEED ; 
 int /*<<< orphan*/  CONNECT ; 
 int /*<<< orphan*/  CONNECT_ACK ; 
 int /*<<< orphan*/  RELEASE ; 
 int /*<<< orphan*/  RELEASE_DONE ; 
 int /*<<< orphan*/  SETUP ; 
 int /*<<< orphan*/  abort () ; 
 struct block* gen_atmfield_code (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct block *
gen_msg_abbrev(compiler_state_t *cstate, int type)
{
	struct block *b1;

	/*
	 * Q.2931 signalling protocol messages for handling virtual circuits
	 * establishment and teardown
	 */
	switch (type) {

	case A_SETUP:
		b1 = gen_atmfield_code(cstate, A_MSGTYPE, SETUP, BPF_JEQ, 0);
		break;

	case A_CALLPROCEED:
		b1 = gen_atmfield_code(cstate, A_MSGTYPE, CALL_PROCEED, BPF_JEQ, 0);
		break;

	case A_CONNECT:
		b1 = gen_atmfield_code(cstate, A_MSGTYPE, CONNECT, BPF_JEQ, 0);
		break;

	case A_CONNECTACK:
		b1 = gen_atmfield_code(cstate, A_MSGTYPE, CONNECT_ACK, BPF_JEQ, 0);
		break;

	case A_RELEASE:
		b1 = gen_atmfield_code(cstate, A_MSGTYPE, RELEASE, BPF_JEQ, 0);
		break;

	case A_RELEASE_DONE:
		b1 = gen_atmfield_code(cstate, A_MSGTYPE, RELEASE_DONE, BPF_JEQ, 0);
		break;

	default:
		abort();
	}
	return b1;
}