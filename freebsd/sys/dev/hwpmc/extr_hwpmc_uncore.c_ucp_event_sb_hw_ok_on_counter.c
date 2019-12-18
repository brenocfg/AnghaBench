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
ucp_event_sb_hw_ok_on_counter(uint8_t ev, int ri)
{
	uint32_t mask;

	switch (ev) {
		/*
		 * Events valid only on counter 0.
		 */
		case 0x80:
		case 0x83:
		mask = (1 << 0);
		break;

	default:
		mask = ~0;	/* Any row index is ok. */
	}

	return (mask & (1 << ri));
}