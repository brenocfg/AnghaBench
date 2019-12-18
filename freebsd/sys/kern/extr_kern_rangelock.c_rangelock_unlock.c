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

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 int /*<<< orphan*/  rangelock_unlock_locked (struct rangelock*,void*,struct mtx*,int) ; 

void
rangelock_unlock(struct rangelock *lock, void *cookie, struct mtx *ilk)
{

	MPASS(lock != NULL && cookie != NULL && ilk != NULL);

	mtx_lock(ilk);
	rangelock_unlock_locked(lock, cookie, ilk, true);
}