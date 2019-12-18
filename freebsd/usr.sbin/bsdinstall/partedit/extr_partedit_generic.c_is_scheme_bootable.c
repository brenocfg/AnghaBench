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

int
is_scheme_bootable(const char *part_type) {
	/*
	 * We don't know anything about this platform, so don't irritate the
	 * user by claiming the chosen partition scheme isn't bootable.
	 */

	return (1);
}