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
 size_t ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pause_reqs ; 
 scalar_t__ pause_sems ; 
 int /*<<< orphan*/  uv_sem_post (scalar_t__) ; 

__attribute__((used)) static void unblock_threadpool(void) {
  size_t i;

  for (i = 0; i < ARRAY_SIZE(pause_reqs); i += 1)
    uv_sem_post(pause_sems + i);
}