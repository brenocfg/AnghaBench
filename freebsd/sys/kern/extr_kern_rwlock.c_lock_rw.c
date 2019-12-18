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
struct rwlock {int dummy; } ;
struct lock_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rw_rlock (struct rwlock*) ; 
 int /*<<< orphan*/  rw_wlock (struct rwlock*) ; 

void
lock_rw(struct lock_object *lock, uintptr_t how)
{
	struct rwlock *rw;

	rw = (struct rwlock *)lock;
	if (how)
		rw_rlock(rw);
	else
		rw_wlock(rw);
}