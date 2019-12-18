#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int k; } ;
struct block {TYPE_1__ s; } ;
typedef  int /*<<< orphan*/  compiler_state_t ;

/* Variables and functions */
 int BPF_K ; 
 int BPF_RET ; 
 struct block* new_block (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct block *
gen_retblk(compiler_state_t *cstate, int v)
{
	struct block *b = new_block(cstate, BPF_RET|BPF_K);

	b->s.k = v;
	return b;
}