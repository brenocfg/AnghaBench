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
struct wake_addr {struct wake_addr* link; } ;
struct pthread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  THR_LOCK_ACQUIRE (struct pthread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THR_LOCK_RELEASE (struct pthread*,int /*<<< orphan*/ *) ; 
 struct pthread* _get_curthread () ; 
 int /*<<< orphan*/  addr_lock ; 
 struct wake_addr default_wake_addr ; 
 struct wake_addr* wake_addr_head ; 

void
_thr_release_wake_addr(struct wake_addr *wa)
{
	struct pthread *curthread = _get_curthread();

	if (wa == &default_wake_addr)
		return;
	THR_LOCK_ACQUIRE(curthread, &addr_lock);
	wa->link = wake_addr_head;
	wake_addr_head = wa;
	THR_LOCK_RELEASE(curthread, &addr_lock);
}