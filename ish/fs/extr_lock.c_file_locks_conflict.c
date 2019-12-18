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
struct file_lock {scalar_t__ owner; scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ F_WRLCK_ ; 
 int /*<<< orphan*/  file_locks_overlap (struct file_lock*,struct file_lock*) ; 

__attribute__((used)) static bool file_locks_conflict(struct file_lock *a, struct file_lock *b) {
    if (a->owner == b->owner)
        return false;
    if (!file_locks_overlap(a, b))
        return false;
    // write locks are incompatible with other types of locks
    if (a->type == F_WRLCK_ || b->type == F_WRLCK_)
        return true;
    return false;
}