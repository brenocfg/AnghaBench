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
typedef  int /*<<< orphan*/  bpf_int32 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_B ; 
 int /*<<< orphan*/  OR_LINKPL ; 
#define  Q_AND 132 
#define  Q_DEFAULT 131 
#define  Q_DST 130 
#define  Q_OR 129 
#define  Q_SRC 128 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  gen_and (struct block*,struct block*) ; 
 struct block* gen_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_or (struct block*,struct block*) ; 
 struct block* gen_portatom6 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

struct block *
gen_portop6(compiler_state_t *cstate, int port, int proto, int dir)
{
	struct block *b0, *b1, *tmp;

	/* ip6 proto 'proto' */
	/* XXX - catch the first fragment of a fragmented packet? */
	b0 = gen_cmp(cstate, OR_LINKPL, 6, BPF_B, (bpf_int32)proto);

	switch (dir) {
	case Q_SRC:
		b1 = gen_portatom6(cstate, 0, (bpf_int32)port);
		break;

	case Q_DST:
		b1 = gen_portatom6(cstate, 2, (bpf_int32)port);
		break;

	case Q_OR:
	case Q_DEFAULT:
		tmp = gen_portatom6(cstate, 0, (bpf_int32)port);
		b1 = gen_portatom6(cstate, 2, (bpf_int32)port);
		gen_or(tmp, b1);
		break;

	case Q_AND:
		tmp = gen_portatom6(cstate, 0, (bpf_int32)port);
		b1 = gen_portatom6(cstate, 2, (bpf_int32)port);
		gen_and(tmp, b1);
		break;

	default:
		abort();
	}
	gen_and(b0, b1);

	return b1;
}