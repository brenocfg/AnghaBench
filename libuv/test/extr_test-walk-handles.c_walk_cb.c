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
 scalar_t__ magic_cookie ; 
 int /*<<< orphan*/  seen_timer_handle ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void walk_cb(uv_handle_t* handle, void* arg) {
  ASSERT(arg == (void*)magic_cookie);

  if (handle == (uv_handle_t*)&timer) {
    seen_timer_handle++;
  } else {
    ASSERT(0 && "unexpected handle");
  }
}