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
 int /*<<< orphan*/  MSG_ERROR ; 
 int TS_DIR_IDX_BIDI ; 
 int TS_DIR_IDX_DOWNLINK ; 
 int TS_DIR_IDX_UPLINK ; 
#define  WMM_AC_DIR_BIDIRECTIONAL 130 
#define  WMM_AC_DIR_DOWNLINK 129 
#define  WMM_AC_DIR_UPLINK 128 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static u8 wmm_ac_direction_to_idx(u8 direction)
{
	switch (direction) {
	case WMM_AC_DIR_UPLINK:
		return TS_DIR_IDX_UPLINK;
	case WMM_AC_DIR_DOWNLINK:
		return TS_DIR_IDX_DOWNLINK;
	case WMM_AC_DIR_BIDIRECTIONAL:
		return TS_DIR_IDX_BIDI;
	default:
		wpa_printf(MSG_ERROR, "Invalid direction: %d", direction);
		return WMM_AC_DIR_UPLINK;
	}
}