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
struct ref_lock {struct ref_lock* ref_name; int /*<<< orphan*/  lk; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ref_lock*) ; 
 int /*<<< orphan*/  rollback_lock_file (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void unlock_ref(struct ref_lock *lock)
{
	rollback_lock_file(&lock->lk);
	free(lock->ref_name);
	free(lock);
}