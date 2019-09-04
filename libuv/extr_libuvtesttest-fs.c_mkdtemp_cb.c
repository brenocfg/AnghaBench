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
typedef  int /*<<< orphan*/  uv_fs_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  check_mkdtemp_result (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mkdtemp_cb_count ; 
 int /*<<< orphan*/  mkdtemp_req1 ; 

__attribute__((used)) static void mkdtemp_cb(uv_fs_t* req) {
  ASSERT(req == &mkdtemp_req1);
  check_mkdtemp_result(req);
  mkdtemp_cb_count++;
}