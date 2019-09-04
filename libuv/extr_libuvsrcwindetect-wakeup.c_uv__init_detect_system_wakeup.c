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

/* Variables and functions */
 int /*<<< orphan*/  uv__register_system_resume_callback () ; 

void uv__init_detect_system_wakeup(void) {
  /* Try registering system power event callback. This is the cleanest
   * method, but it will only work on Win8 and above.
   */
  uv__register_system_resume_callback();
}