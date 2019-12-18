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
#define  DEST_AUTO 130 
#define  DEST_HDMI 129 
#define  DEST_HEADPHONES 128 

__attribute__((used)) static const char *
dest_description(uint32_t dest)
{
	switch (dest) {
		case DEST_AUTO:
			return "AUTO";
			break;

		case DEST_HEADPHONES:
			return "HEADPHONES";
			break;

		case DEST_HDMI:
			return "HDMI";
			break;
		default:
			return "UNKNOWN";
			break;
	}
}