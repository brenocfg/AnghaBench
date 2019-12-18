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
struct file_lock {int /*<<< orphan*/  locks; int /*<<< orphan*/  pid; int /*<<< orphan*/  owner; int /*<<< orphan*/  type; int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 
 struct file_lock* malloc (int) ; 

__attribute__((used)) static struct file_lock *file_lock_copy(struct file_lock *request) {
    struct file_lock *lock = malloc(sizeof(struct file_lock));
    lock->start = request->start;
    lock->end = request->end;
    lock->type = request->type;
    lock->owner = request->owner;
    lock->pid = request->pid;
    list_init(&lock->locks);
    return lock;
}