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
typedef  int uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,size_t,char*,...) ; 

void
mfi_autolearn_mode(uint8_t mode, char *buf, size_t sz)
{

	switch (mode) {
	case 0:
		snprintf(buf, sz, "enabled");
		break;
	case 1:
		snprintf(buf, sz, "disabled");
		break;
	case 2:
		snprintf(buf, sz, "warn via event");
		break;
	default:
		snprintf(buf, sz, "mode 0x%02x", mode);
		break;
	}
}