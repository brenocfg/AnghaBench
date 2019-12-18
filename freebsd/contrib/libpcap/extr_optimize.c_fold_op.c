#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stmt {int code; int k; } ;
struct TYPE_5__ {scalar_t__ done; TYPE_1__* vmap; } ;
typedef  TYPE_2__ opt_state_t ;
typedef  int /*<<< orphan*/  compiler_state_t ;
typedef  int bpf_u_int32 ;
struct TYPE_4__ {int const_val; } ;

/* Variables and functions */
#define  BPF_ADD 137 
#define  BPF_AND 136 
#define  BPF_DIV 135 
 int BPF_IMM ; 
 int BPF_LD ; 
#define  BPF_LSH 134 
#define  BPF_MOD 133 
#define  BPF_MUL 132 
 int BPF_OP (int) ; 
#define  BPF_OR 131 
#define  BPF_RSH 130 
#define  BPF_SUB 129 
#define  BPF_XOR 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  bpf_error (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
fold_op(compiler_state_t *cstate, opt_state_t *opt_state,
    struct stmt *s, int v0, int v1)
{
	bpf_u_int32 a, b;

	a = opt_state->vmap[v0].const_val;
	b = opt_state->vmap[v1].const_val;

	switch (BPF_OP(s->code)) {
	case BPF_ADD:
		a += b;
		break;

	case BPF_SUB:
		a -= b;
		break;

	case BPF_MUL:
		a *= b;
		break;

	case BPF_DIV:
		if (b == 0)
			bpf_error(cstate, "division by zero");
		a /= b;
		break;

	case BPF_MOD:
		if (b == 0)
			bpf_error(cstate, "modulus by zero");
		a %= b;
		break;

	case BPF_AND:
		a &= b;
		break;

	case BPF_OR:
		a |= b;
		break;

	case BPF_XOR:
		a ^= b;
		break;

	case BPF_LSH:
		a <<= b;
		break;

	case BPF_RSH:
		a >>= b;
		break;

	default:
		abort();
	}
	s->k = a;
	s->code = BPF_LD|BPF_IMM;
	opt_state->done = 0;
}