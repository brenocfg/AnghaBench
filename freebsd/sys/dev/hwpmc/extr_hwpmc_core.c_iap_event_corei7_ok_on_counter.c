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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static int
iap_event_corei7_ok_on_counter(uint8_t evsel, int ri)
{
	uint32_t mask;

	switch (evsel) {
		/*
		 * Events valid only on counter 0, 1.
		 */
		case 0x40:
		case 0x41:
		case 0x42:
		case 0x43:
		case 0x51:
		case 0x63:
			mask = 0x3;
		break;

		default:
		mask = ~0;	/* Any row index is ok. */
	}

	return (mask & (1 << ri));
}