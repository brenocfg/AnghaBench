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
 int TD_T ; 
#define  TD_T_CARRY 130 
#define  TD_T_DATA0 129 
#define  TD_T_DATA1 128 

__attribute__((used)) static inline char *td_togglestring(u32 info)
{
	switch (info & TD_T) {
	case TD_T_DATA0:
		return "DATA0";
	case TD_T_DATA1:
		return "DATA1";
	case TD_T_CARRY:
		return "CARRY";
	}
	return "?TOGGLE";
}