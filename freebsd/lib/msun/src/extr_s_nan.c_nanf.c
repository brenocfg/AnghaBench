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

float
nanf(const char *s)
{
	union {
		float f;
		uint32_t bits[1];
	} u;

	_scan_nan(u.bits, 1, s);
	u.bits[0] |= 0x7fc00000;
	return (u.f);
}