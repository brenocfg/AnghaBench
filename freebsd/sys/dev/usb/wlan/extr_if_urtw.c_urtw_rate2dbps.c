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

__attribute__((used)) static uint16_t
urtw_rate2dbps(uint16_t rate)
{

	switch(rate) {
	case 12:
	case 18:
	case 24:
	case 36:
	case 48:
	case 72:
	case 96:
	case 108:
		return (rate * 2);
	default:
		break;
	}
	return (24);
}