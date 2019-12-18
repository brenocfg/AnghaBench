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
typedef  scalar_t__ vm_offset_t ;
struct futex_st0 {int oparg; int* oldval; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_fcmpset_int (int*,int*,int) ; 

__attribute__((used)) static void
futex_xorl_slow0(vm_offset_t kva, void *arg)
{
	struct futex_st0 *st;
	int old;

	st = arg;
	old = *(int *)kva;
	while (!atomic_fcmpset_int((int *)kva, &old, old ^ st->oparg))
		;
	*st->oldval = old;
}