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
typedef  int u32 ;

/* Variables and functions */
 int TD_DP ; 
#define  TD_DP_IN 130 
#define  TD_DP_OUT 129 
#define  TD_DP_SETUP 128 

__attribute__((used)) static inline char *td_pidstring(u32 info)
{
	switch (info & TD_DP) {
	case TD_DP_SETUP:
		return "SETUP";
	case TD_DP_IN:
		return "IN";
	case TD_DP_OUT:
		return "OUT";
	}
	return "?PID";
}