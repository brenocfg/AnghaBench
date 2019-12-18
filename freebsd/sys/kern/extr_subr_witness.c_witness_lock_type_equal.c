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
struct witness {TYPE_1__* w_class; } ;
struct TYPE_2__ {int lc_flags; } ;

/* Variables and functions */
 int LC_SLEEPLOCK ; 
 int LC_SPINLOCK ; 

__attribute__((used)) static __inline int
witness_lock_type_equal(struct witness *w1, struct witness *w2)
{

	return ((w1->w_class->lc_flags & (LC_SLEEPLOCK | LC_SPINLOCK)) ==
		(w2->w_class->lc_flags & (LC_SLEEPLOCK | LC_SPINLOCK)));
}