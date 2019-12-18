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
typedef  int /*<<< orphan*/  uv_signal_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  uv__is_closing (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__signal_stop (int /*<<< orphan*/ *) ; 

int uv_signal_stop(uv_signal_t* handle) {
  assert(!uv__is_closing(handle));
  uv__signal_stop(handle);
  return 0;
}