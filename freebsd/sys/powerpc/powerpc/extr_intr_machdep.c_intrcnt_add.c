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
typedef  int /*<<< orphan*/  u_long ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int atomic_fetchadd_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * intrcnt ; 
 int /*<<< orphan*/  intrcnt_index ; 
 int /*<<< orphan*/  intrcnt_setname (char const*,int) ; 
 int nintrcnt ; 

void
intrcnt_add(const char *name, u_long **countp)
{
	int idx;

	idx = atomic_fetchadd_int(&intrcnt_index, 1);
	KASSERT(idx < nintrcnt, ("intrcnt_add: Interrupt counter index %d/%d"
		"reached nintrcnt : %d", intrcnt_index, idx, nintrcnt));
	*countp = &intrcnt[idx];
	intrcnt_setname(name, idx);
}