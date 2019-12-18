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
struct stack {int depth; scalar_t__* pcs; } ;
typedef  int /*<<< orphan*/  namebuf ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int STACK_MAX ; 
 int /*<<< orphan*/  printf (char*,int,void*,char*,long) ; 
 int /*<<< orphan*/  stack_symbol (scalar_t__,char*,int,long*,int /*<<< orphan*/ ) ; 

void
stack_print(const struct stack *st)
{
	char namebuf[64];
	long offset;
	int i;

	KASSERT(st->depth <= STACK_MAX, ("bogus stack"));
	for (i = 0; i < st->depth; i++) {
		(void)stack_symbol(st->pcs[i], namebuf, sizeof(namebuf),
		    &offset, M_WAITOK);
		printf("#%d %p at %s+%#lx\n", i, (void *)st->pcs[i],
		    namebuf, offset);
	}
}