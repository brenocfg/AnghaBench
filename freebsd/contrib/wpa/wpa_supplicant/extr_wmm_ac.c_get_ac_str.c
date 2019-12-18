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
#define  WMM_AC_BE 131 
#define  WMM_AC_BK 130 
#define  WMM_AC_VI 129 
#define  WMM_AC_VO 128 

__attribute__((used)) static const char * get_ac_str(u8 ac)
{
	switch (ac) {
	case WMM_AC_BE:
		return "BE";
	case WMM_AC_BK:
		return "BK";
	case WMM_AC_VI:
		return "VI";
	case WMM_AC_VO:
		return "VO";
	default:
		return "N/A";
	}
}