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
 scalar_t__ completed_pingers ; 
 int /*<<< orphan*/  pinger_shutdown_cb_called ; 

__attribute__((used)) static void pinger_shutdown_cb(uv_shutdown_t* req, int status) {
  ASSERT(status == 0);
  pinger_shutdown_cb_called++;

  /*
   * The close callback has not been triggered yet. We must wait for EOF
   * until we close the connection.
   */
  ASSERT(completed_pingers == 0);
}