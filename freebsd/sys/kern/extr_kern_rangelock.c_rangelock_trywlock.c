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
struct rangelock {int dummy; } ;
struct mtx {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  RL_LOCK_WRITE ; 
 void* rangelock_enqueue (struct rangelock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mtx*,int) ; 

void *
rangelock_trywlock(struct rangelock *lock, off_t start, off_t end,
    struct mtx *ilk)
{

	return (rangelock_enqueue(lock, start, end, RL_LOCK_WRITE, ilk, true));
}