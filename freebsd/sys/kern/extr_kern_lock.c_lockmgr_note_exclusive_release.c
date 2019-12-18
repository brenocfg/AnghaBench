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
struct lock {int /*<<< orphan*/  lock_object; int /*<<< orphan*/  lk_recurse; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCKSTAT_PROFILE_RELEASE_RWLOCK (int /*<<< orphan*/ ,struct lock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCKSTAT_WRITER ; 
 int /*<<< orphan*/  LOCK_LOG_LOCK (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  LOP_EXCLUSIVE ; 
 int /*<<< orphan*/  TD_LOCKS_DEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WITNESS_UNLOCK (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  lockmgr__release ; 

__attribute__((used)) static void
lockmgr_note_exclusive_release(struct lock *lk, const char *file, int line)
{

	LOCKSTAT_PROFILE_RELEASE_RWLOCK(lockmgr__release, lk, LOCKSTAT_WRITER);
	LOCK_LOG_LOCK("XUNLOCK", &lk->lock_object, 0, lk->lk_recurse, file,
	    line);
	WITNESS_UNLOCK(&lk->lock_object, LOP_EXCLUSIVE, file, line);
	TD_LOCKS_DEC(curthread);
}