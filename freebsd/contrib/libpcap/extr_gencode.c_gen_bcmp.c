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
typedef  int u_int ;
typedef  int u_char ;
struct block {int dummy; } ;
typedef  enum e_offrel { ____Placeholder_e_offrel } e_offrel ;
typedef  int /*<<< orphan*/  compiler_state_t ;
typedef  int bpf_int32 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_B ; 
 int /*<<< orphan*/  BPF_H ; 
 int /*<<< orphan*/  BPF_W ; 
 int /*<<< orphan*/  gen_and (struct block*,struct block*) ; 
 struct block* gen_cmp (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct block *
gen_bcmp(compiler_state_t *cstate, enum e_offrel offrel, u_int offset,
    u_int size, const u_char *v)
{
	register struct block *b, *tmp;

	b = NULL;
	while (size >= 4) {
		register const u_char *p = &v[size - 4];
		bpf_int32 w = ((bpf_int32)p[0] << 24) |
		    ((bpf_int32)p[1] << 16) | ((bpf_int32)p[2] << 8) | p[3];

		tmp = gen_cmp(cstate, offrel, offset + size - 4, BPF_W, w);
		if (b != NULL)
			gen_and(b, tmp);
		b = tmp;
		size -= 4;
	}
	while (size >= 2) {
		register const u_char *p = &v[size - 2];
		bpf_int32 w = ((bpf_int32)p[0] << 8) | p[1];

		tmp = gen_cmp(cstate, offrel, offset + size - 2, BPF_H, w);
		if (b != NULL)
			gen_and(b, tmp);
		b = tmp;
		size -= 2;
	}
	if (size > 0) {
		tmp = gen_cmp(cstate, offrel, offset, BPF_B, (bpf_int32)v[0]);
		if (b != NULL)
			gen_and(b, tmp);
		b = tmp;
	}
	return b;
}