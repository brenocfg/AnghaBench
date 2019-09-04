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
typedef  int /*<<< orphan*/  uv_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  once_close_cb_called ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ uv_is_active (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void once_close_cb(uv_handle_t* handle) {
  printf("ONCE_CLOSE_CB\n");

  ASSERT(handle != NULL);
  ASSERT(0 == uv_is_active(handle));

  once_close_cb_called++;
}