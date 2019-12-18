#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int exp; int manh; } ;
union IEEEl2bits {long double e; TYPE_1__ bits; } ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  _scan_nan (int /*<<< orphan*/ *,int,char const*) ; 

long double
nanl(const char *s)
{
	union {
		union IEEEl2bits ieee;
		uint32_t bits[3];
	} u;

	_scan_nan(u.bits, 3, s);
	u.ieee.bits.exp = 0x7fff;
	u.ieee.bits.manh |= 0xc0000000;	/* make it a quiet NaN */
	return (u.ieee.e);
}