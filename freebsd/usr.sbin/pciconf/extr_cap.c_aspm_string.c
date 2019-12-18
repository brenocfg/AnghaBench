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

__attribute__((used)) static const char *
aspm_string(uint8_t aspm)
{

	switch (aspm) {
	case 1:
		return ("L0s");
	case 2:
		return ("L1");
	case 3:
		return ("L0s/L1");
	default:
		return ("disabled");
	}
}