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
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  main_thread_id ; 
 scalar_t__ uv_thread_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_thread_self () ; 

__attribute__((used)) static void check_thread(void* arg) {
  uv_thread_t *thread_id = arg;
  uv_thread_t self_id = uv_thread_self();
  ASSERT(uv_thread_equal(&main_thread_id, &self_id) == 0);
  *thread_id = uv_thread_self();
}