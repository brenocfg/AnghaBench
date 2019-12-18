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

/* Variables and functions */
 int /*<<< orphan*/  blocker ; 
 int /*<<< orphan*/  numlock ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 
 int shared_num ; 
 int /*<<< orphan*/  uv_barrier_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_rwlock_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_rwlock_rdunlock (int /*<<< orphan*/ *) ; 

void reader(void *n)
{
    int num = *(int *)n;
    int i;
    for (i = 0; i < 20; i++) {
        uv_rwlock_rdlock(&numlock);
        printf("Reader %d: acquired lock\n", num);
        printf("Reader %d: shared num = %d\n", num, shared_num);
        uv_rwlock_rdunlock(&numlock);
        printf("Reader %d: released lock\n", num);
    }
    uv_barrier_wait(&blocker);
}