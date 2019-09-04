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
 int /*<<< orphan*/  work_cb_count ; 

__attribute__((used)) static void work_cb(uv_work_t* req) {
  work_cb_count++;
}