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
 int /*<<< orphan*/  CHECK_HANDLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close_cb_called ; 
 int uv_is_closing (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void close_cb(uv_handle_t* handle) {
  CHECK_HANDLE(handle);
  ASSERT(1 == uv_is_closing(handle));
  close_cb_called++;
}