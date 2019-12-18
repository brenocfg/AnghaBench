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
typedef  size_t u32 ;
struct bpf_jit {int* seen_reg; } ;

/* Variables and functions */
 size_t* reg2hex ; 

__attribute__((used)) static inline void reg_set_seen(struct bpf_jit *jit, u32 b1)
{
	u32 r1 = reg2hex[b1];

	if (!jit->seen_reg[r1] && r1 >= 6 && r1 <= 15)
		jit->seen_reg[r1] = 1;
}