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
typedef  int /*<<< orphan*/  RtldLockState ;

/* Variables and functions */
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  libmap_disable ; 
 int /*<<< orphan*/  list_fini ; 
 int /*<<< orphan*/  lm_fini () ; 
 int /*<<< orphan*/  lock_release (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  objlist_call_fini (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtld_bind_lock ; 
 int /*<<< orphan*/  wlock_acquire (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
rtld_exit(void)
{
    RtldLockState lockstate;

    wlock_acquire(rtld_bind_lock, &lockstate);
    dbg("rtld_exit()");
    objlist_call_fini(&list_fini, NULL, &lockstate);
    /* No need to remove the items from the list, since we are exiting. */
    if (!libmap_disable)
        lm_fini();
    lock_release(rtld_bind_lock, &lockstate);
}