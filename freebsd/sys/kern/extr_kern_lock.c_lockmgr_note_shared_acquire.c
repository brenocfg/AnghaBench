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
typedef  int /*<<< orphan*/  uint64_t ;
struct lock {int /*<<< orphan*/  lock_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  LK_TRYWIT (int) ; 
 int /*<<< orphan*/  LOCKSTAT_PROFILE_OBTAIN_RWLOCK_SUCCESS (int /*<<< orphan*/ ,struct lock*,int,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCKSTAT_READER ; 
 int /*<<< orphan*/  LOCK_LOG_LOCK (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  STACK_SAVE (struct lock*) ; 
 int /*<<< orphan*/  TD_LOCKS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TD_SLOCKS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WITNESS_LOCK (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  lockmgr__acquire ; 

__attribute__((used)) static void
lockmgr_note_shared_acquire(struct lock *lk, int contested,
    uint64_t waittime, const char *file, int line, int flags)
{

	LOCKSTAT_PROFILE_OBTAIN_RWLOCK_SUCCESS(lockmgr__acquire, lk, contested,
	    waittime, file, line, LOCKSTAT_READER);
	LOCK_LOG_LOCK("SLOCK", &lk->lock_object, 0, 0, file, line);
	WITNESS_LOCK(&lk->lock_object, LK_TRYWIT(flags), file, line);
	TD_LOCKS_INC(curthread);
	TD_SLOCKS_INC(curthread);
	STACK_SAVE(lk);
}