#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct edge {int code; TYPE_2__* pred; } ;
struct TYPE_3__ {int code; } ;
struct block {int* val; int oval; TYPE_1__ s; } ;
struct TYPE_4__ {int* val; int oval; } ;

/* Variables and functions */
 size_t A_ATOM ; 
 int BPF_JEQ ; 
 int BPF_JMP ; 
 int BPF_K ; 
 struct block* JF (struct block*) ; 
 struct block* JT (struct block*) ; 

__attribute__((used)) static struct block *
fold_edge(struct block *child, struct edge *ep)
{
	int sense;
	int aval0, aval1, oval0, oval1;
	int code = ep->code;

	if (code < 0) {
		code = -code;
		sense = 0;
	} else
		sense = 1;

	if (child->s.code != code)
		return 0;

	aval0 = child->val[A_ATOM];
	oval0 = child->oval;
	aval1 = ep->pred->val[A_ATOM];
	oval1 = ep->pred->oval;

	if (aval0 != aval1)
		return 0;

	if (oval0 == oval1)
		/*
		 * The operands of the branch instructions are
		 * identical, so the result is true if a true
		 * branch was taken to get here, otherwise false.
		 */
		return sense ? JT(child) : JF(child);

	if (sense && code == (BPF_JMP|BPF_JEQ|BPF_K))
		/*
		 * At this point, we only know the comparison if we
		 * came down the true branch, and it was an equality
		 * comparison with a constant.
		 *
		 * I.e., if we came down the true branch, and the branch
		 * was an equality comparison with a constant, we know the
		 * accumulator contains that constant.  If we came down
		 * the false branch, or the comparison wasn't with a
		 * constant, we don't know what was in the accumulator.
		 *
		 * We rely on the fact that distinct constants have distinct
		 * value numbers.
		 */
		return JF(child);

	return 0;
}