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
typedef  int u8 ;

/* Variables and functions */
#define  WMM_AC_DIR_BIDIRECTIONAL 130 
#define  WMM_AC_DIR_DOWNLINK 129 
#define  WMM_AC_DIR_UPLINK 128 

__attribute__((used)) static const char * get_direction_str(u8 direction)
{
	switch (direction) {
	case WMM_AC_DIR_DOWNLINK:
		return "Downlink";
	case WMM_AC_DIR_UPLINK:
		return "Uplink";
	case WMM_AC_DIR_BIDIRECTIONAL:
		return "Bi-directional";
	default:
		return "N/A";
	}
}