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
typedef  enum e_offrel { ____Placeholder_e_offrel } e_offrel ;
typedef  int /*<<< orphan*/  compiler_state_t ;
typedef  int /*<<< orphan*/  bpf_int32 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_B ; 
 int /*<<< orphan*/  BPF_W ; 
 int GENEVE_PORT ; 
 int IPPROTO_UDP ; 
 int Q_DST ; 
 int /*<<< orphan*/  gen_and (struct block*,struct block*) ; 
 struct block* gen_mcmp (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct block *
gen_geneve_check(compiler_state_t *cstate,
    struct block *(*gen_portfn)(compiler_state_t *, int, int, int),
    enum e_offrel offrel, int vni)
{
	struct block *b0, *b1;

	b0 = gen_portfn(cstate, GENEVE_PORT, IPPROTO_UDP, Q_DST);

	/* Check that we are operating on version 0. Otherwise, we
	 * can't decode the rest of the fields. The version is 2 bits
	 * in the first byte of the Geneve header. */
	b1 = gen_mcmp(cstate, offrel, 8, BPF_B, (bpf_int32)0, 0xc0);
	gen_and(b0, b1);
	b0 = b1;

	if (vni >= 0) {
		vni <<= 8; /* VNI is in the upper 3 bytes */
		b1 = gen_mcmp(cstate, offrel, 12, BPF_W, (bpf_int32)vni,
			      0xffffff00);
		gen_and(b0, b1);
		b0 = b1;
	}

	return b0;
}