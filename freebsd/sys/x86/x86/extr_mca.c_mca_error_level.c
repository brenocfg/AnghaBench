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
typedef  int uint16_t ;

/* Variables and functions */

__attribute__((used)) static const char *
mca_error_level(uint16_t mca_error)
{

	switch (mca_error & 0x0003) {
	case 0:
		return ("L0");
	case 1:
		return ("L1");
	case 2:
		return ("L2");
	case 3:
		return ("LG");
	}
	return ("L?");
}