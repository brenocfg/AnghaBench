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
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  condvar ; 
 int /*<<< orphan*/  mutex ; 
 int step ; 
 int /*<<< orphan*/  synchronize_nowait () ; 
 int /*<<< orphan*/  uv_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void synchronize(void) {
  int current;

  synchronize_nowait();
  /* Wait for the other thread.  Guard against spurious wakeups. */
  for (current = step; current == step; uv_cond_wait(&condvar, &mutex));
  ASSERT(step == current + 1);
}