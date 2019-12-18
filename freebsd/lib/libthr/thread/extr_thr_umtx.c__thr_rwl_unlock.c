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
struct urwlock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PANIC (char*) ; 
 scalar_t__ _thr_rwlock_unlock (struct urwlock*) ; 

void
_thr_rwl_unlock(struct urwlock *rwlock)
{

	if (_thr_rwlock_unlock(rwlock))
		PANIC("unlock error");
}