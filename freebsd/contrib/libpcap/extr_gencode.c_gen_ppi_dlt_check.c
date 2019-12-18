#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int k; } ;
struct slist {TYPE_1__ s; } ;
struct TYPE_8__ {int /*<<< orphan*/  k; } ;
struct block {TYPE_2__ s; struct slist* stmts; } ;
struct TYPE_9__ {scalar_t__ linktype; } ;
typedef  TYPE_3__ compiler_state_t ;

/* Variables and functions */
 int BPF_ABS ; 
 int /*<<< orphan*/  BPF_JEQ ; 
 int BPF_LD ; 
 int BPF_W ; 
 int /*<<< orphan*/  DLT_IEEE802_11 ; 
 scalar_t__ DLT_PPI ; 
 int /*<<< orphan*/  JMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWAPLONG (int /*<<< orphan*/ ) ; 
 struct block* new_block (TYPE_3__*,int /*<<< orphan*/ ) ; 
 struct slist* new_stmt (TYPE_3__*,int) ; 

__attribute__((used)) static struct block *
gen_ppi_dlt_check(compiler_state_t *cstate)
{
	struct slist *s_load_dlt;
	struct block *b;

	if (cstate->linktype == DLT_PPI)
	{
		/* Create the statements that check for the DLT
		 */
		s_load_dlt = new_stmt(cstate, BPF_LD|BPF_W|BPF_ABS);
		s_load_dlt->s.k = 4;

		b = new_block(cstate, JMP(BPF_JEQ));

		b->stmts = s_load_dlt;
		b->s.k = SWAPLONG(DLT_IEEE802_11);
	}
	else
	{
		b = NULL;
	}

	return b;
}