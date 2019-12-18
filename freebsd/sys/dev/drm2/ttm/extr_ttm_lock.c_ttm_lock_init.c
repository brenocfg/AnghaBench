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
struct ttm_lock {int kill_takers; int /*<<< orphan*/  signal; scalar_t__ flags; scalar_t__ rw; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ttm_lock_init(struct ttm_lock *lock)
{
	mtx_init(&lock->lock, "ttmlk", NULL, MTX_DEF);
	lock->rw = 0;
	lock->flags = 0;
	lock->kill_takers = false;
	lock->signal = SIGKILL;
}