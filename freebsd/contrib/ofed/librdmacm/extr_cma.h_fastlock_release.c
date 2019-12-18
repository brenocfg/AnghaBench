#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  sem; int /*<<< orphan*/  cnt; } ;
typedef  TYPE_1__ fastlock_t ;

/* Variables and functions */
 int atomic_fetch_sub (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sem_post (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void fastlock_release(fastlock_t *lock)
{
	if (atomic_fetch_sub(&lock->cnt, 1) > 1)
		sem_post(&lock->sem);
}