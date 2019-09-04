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
typedef  int /*<<< orphan*/  uv_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  blocker ; 
 int /*<<< orphan*/  numlock ; 
 int /*<<< orphan*/  reader ; 
 scalar_t__ shared_num ; 
 int /*<<< orphan*/  uv_barrier_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_barrier_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uv_barrier_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_rwlock_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_thread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  writer ; 

int main()
{
    uv_barrier_init(&blocker, 4);

    shared_num = 0;
    uv_rwlock_init(&numlock);

    uv_thread_t threads[3];

    int thread_nums[] = {1, 2, 1};
    uv_thread_create(&threads[0], reader, &thread_nums[0]);
    uv_thread_create(&threads[1], reader, &thread_nums[1]);

    uv_thread_create(&threads[2], writer, &thread_nums[2]);

    uv_barrier_wait(&blocker);
    uv_barrier_destroy(&blocker);

    uv_rwlock_destroy(&numlock);
    return 0;
}