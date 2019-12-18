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
 int WMM_AC_ECWMAX_MASK ; 
 int WMM_AC_ECWMAX_SHIFT ; 
 int WMM_AC_ECWMIN_MASK ; 
 int WMM_AC_ECWMIN_SHIFT ; 

__attribute__((used)) static inline u8 wmm_ecw(int ecwmin, int ecwmax)
{
	return ((ecwmin << WMM_AC_ECWMIN_SHIFT) & WMM_AC_ECWMIN_MASK) |
		((ecwmax << WMM_AC_ECWMAX_SHIFT) & WMM_AC_ECWMAX_MASK);
}