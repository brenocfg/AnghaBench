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
struct thread {int dummy; } ;
struct lock {uintptr_t lk_lock; } ;

/* Variables and functions */
 scalar_t__ LK_HOLDER (uintptr_t) ; 
 uintptr_t LK_SHARE ; 

__attribute__((used)) static __inline struct thread *
lockmgr_xholder(const struct lock *lk)
{
	uintptr_t x;

	x = lk->lk_lock;
	return ((x & LK_SHARE) ? NULL : (struct thread *)LK_HOLDER(x));
}