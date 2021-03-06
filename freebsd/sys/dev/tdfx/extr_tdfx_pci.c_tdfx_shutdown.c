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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
tdfx_shutdown(device_t dev) {
#ifdef DEBUG
	device_printf(dev, "tdfx: Device Shutdown\n");
#endif
	return 0;
}