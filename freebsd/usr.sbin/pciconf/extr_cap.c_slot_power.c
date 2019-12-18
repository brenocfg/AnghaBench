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
 int PCIEM_SLOT_CAP_SPLS ; 
 int PCIEM_SLOT_CAP_SPLV ; 

__attribute__((used)) static int
slot_power(uint32_t cap)
{
	int mwatts;

	mwatts = (cap & PCIEM_SLOT_CAP_SPLV) >> 7;
	switch (cap & PCIEM_SLOT_CAP_SPLS) {
	case 0x0:
		mwatts *= 1000;
		break;
	case 0x1:
		mwatts *= 100;
		break;
	case 0x2:
		mwatts *= 10;
		break;
	default:
		break;
	}
	return (mwatts);
}