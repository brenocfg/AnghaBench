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
 int /*<<< orphan*/  uv__loops_lock ; 
 int /*<<< orphan*/  uv_mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void uv__loops_init(void) {
  uv_mutex_init(&uv__loops_lock);
}