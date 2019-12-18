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
typedef  int /*<<< orphan*/  uv_shutdown_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  shutdown_cb_called ; 
 int /*<<< orphan*/  shutdown_req ; 

__attribute__((used)) static void shutdown_cb(uv_shutdown_t* req, int status) {
  ASSERT(req == &shutdown_req);
  shutdown_cb_called++;
}