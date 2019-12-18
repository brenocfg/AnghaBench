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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  _scan_nan (int*,int,char const*) ; 

double
nan(const char *s)
{
	union {
		double d;
		uint32_t bits[2];
	} u;

	_scan_nan(u.bits, 2, s);
#if _BYTE_ORDER == _LITTLE_ENDIAN
	u.bits[1] |= 0x7ff80000;
#else
	u.bits[0] |= 0x7ff80000;
#endif
	return (u.d);
}