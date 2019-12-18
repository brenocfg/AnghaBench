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
typedef  int /*<<< orphan*/  uv_barrier_t ;

/* Variables and functions */
 int /*<<< orphan*/  uv_barrier_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ uv_barrier_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_sleep (int) ; 

__attribute__((used)) static void serial_worker(void* data) {
  uv_barrier_t* barrier;

  barrier = data;
  if (uv_barrier_wait(barrier) > 0)
    uv_barrier_destroy(barrier);

  uv_sleep(100);  /* Wait a bit before terminating. */
}