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
typedef  int /*<<< orphan*/  wl_fixed_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct wl_data_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void motion(void *data, struct wl_data_device *wl_data_device, uint32_t time, wl_fixed_t x, wl_fixed_t y) {
}