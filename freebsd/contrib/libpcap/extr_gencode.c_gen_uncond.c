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
struct slist {TYPE_1__ s; } ;
struct block {struct slist* stmts; } ;
typedef  int /*<<< orphan*/  compiler_state_t ;

/* Variables and functions */
 int BPF_IMM ; 
 int /*<<< orphan*/  BPF_JEQ ; 
 int BPF_LD ; 
 int /*<<< orphan*/  JMP (int /*<<< orphan*/ ) ; 
 struct block* new_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct slist* new_stmt (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct block *
gen_uncond(compiler_state_t *cstate, int rsense)
{
	struct block *b;
	struct slist *s;

	s = new_stmt(cstate, BPF_LD|BPF_IMM);
	s->s.k = !rsense;
	b = new_block(cstate, JMP(BPF_JEQ));
	b->stmts = s;

	return b;
}