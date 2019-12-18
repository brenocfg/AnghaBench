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
struct flock_ {scalar_t__ start; scalar_t__ len; int /*<<< orphan*/  pid; int /*<<< orphan*/  whence; int /*<<< orphan*/  type; } ;
struct file_lock {scalar_t__ start; scalar_t__ end; int /*<<< orphan*/  pid; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  LSEEK_SET ; 
 scalar_t__ OFF_T_MAX ; 

__attribute__((used)) static int flock_from_file_lock(struct file_lock *lock, struct flock_ *flock) {
    flock->type = lock->type;
    flock->whence = LSEEK_SET;
    flock->start = lock->start;
    if (lock->end != OFF_T_MAX)
        flock->len = lock->end - lock->start + 1;
    else
        flock->len = 0;
    flock->pid = lock->pid;
    return 0;
}