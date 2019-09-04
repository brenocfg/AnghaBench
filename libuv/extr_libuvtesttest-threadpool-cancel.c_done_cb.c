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
typedef  int /*<<< orphan*/  uv_work_t ;

/* Variables and functions */
 int /*<<< orphan*/ * pause_reqs ; 
 int pause_sems ; 
 int /*<<< orphan*/  uv_sem_destroy (int) ; 

__attribute__((used)) static void done_cb(uv_work_t* req, int status) {
  uv_sem_destroy(pause_sems + (req - pause_reqs));
}