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

__attribute__((used)) static inline int ttlv_valid(uint16_t ttlv)
{
	if (ttlv > 0) {
		if (ttlv == 1 || ttlv == 0x1000)
			return 1;
		if (ttlv >= 0x10 && ttlv <= 0x11)
			return 1;
		if (ttlv >= 0x110 && ttlv <= 0x116)
			return 1;
		if (ttlv >= 0x8000)
			return 0;	/* XXX: */
	}

	return 0;
}