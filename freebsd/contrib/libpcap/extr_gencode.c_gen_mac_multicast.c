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
struct slist {int dummy; } ;
struct TYPE_2__ {int k; } ;
struct block {struct slist* stmts; TYPE_1__ s; } ;
typedef  int /*<<< orphan*/  compiler_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_B ; 
 int /*<<< orphan*/  BPF_JSET ; 
 int /*<<< orphan*/  JMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OR_LINKHDR ; 
 struct slist* gen_load_a (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct block* new_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct block *
gen_mac_multicast(compiler_state_t *cstate, int offset)
{
	register struct block *b0;
	register struct slist *s;

	/* link[offset] & 1 != 0 */
	s = gen_load_a(cstate, OR_LINKHDR, offset, BPF_B);
	b0 = new_block(cstate, JMP(BPF_JSET));
	b0->s.k = 1;
	b0->stmts = s;
	return b0;
}