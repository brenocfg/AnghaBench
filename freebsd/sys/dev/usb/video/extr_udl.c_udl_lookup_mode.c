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
typedef  size_t uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_2__ {scalar_t__ hdisplay; scalar_t__ vdisplay; scalar_t__ clock; scalar_t__ chip; size_t hz; } ;

/* Variables and functions */
 size_t UDL_MAX_MODES ; 
 TYPE_1__* udl_modes ; 

__attribute__((used)) static uint8_t
udl_lookup_mode(uint16_t hdisplay, uint16_t vdisplay, uint8_t hz,
    uint16_t chip, uint32_t clock)
{
	uint8_t idx;

	/*
	 * Check first if we have a matching mode with pixelclock
	 */
	for (idx = 0; idx != UDL_MAX_MODES; idx++) {
		if ((udl_modes[idx].hdisplay == hdisplay) &&
		    (udl_modes[idx].vdisplay == vdisplay) &&
		    (udl_modes[idx].clock == clock) &&
		    (udl_modes[idx].chip <= chip)) {
			return (idx);
		}
	}

	/*
	 * If not, check for matching mode with update frequency
	 */
	for (idx = 0; idx != UDL_MAX_MODES; idx++) {
		if ((udl_modes[idx].hdisplay == hdisplay) &&
		    (udl_modes[idx].vdisplay == vdisplay) &&
		    (udl_modes[idx].hz == hz) &&
		    (udl_modes[idx].chip <= chip)) {
			return (idx);
		}
	}
	return (idx);
}