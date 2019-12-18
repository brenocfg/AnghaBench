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
struct block {TYPE_1__ s; struct slist* stmts; } ;
typedef  int /*<<< orphan*/  compiler_state_t ;

/* Variables and functions */
 int BPF_LD ; 
 int BPF_LEN ; 
 int /*<<< orphan*/  JMP (int) ; 
 struct block* new_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct slist* new_stmt (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct block *
gen_len(compiler_state_t *cstate, int jmp, int n)
{
	struct slist *s;
	struct block *b;

	s = new_stmt(cstate, BPF_LD|BPF_LEN);
	b = new_block(cstate, JMP(jmp));
	b->stmts = s;
	b->s.k = n;

	return b;
}