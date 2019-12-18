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
typedef  enum uni_addr_screen { ____Placeholder_uni_addr_screen } uni_addr_screen ;
typedef  enum uni_addr_pres { ____Placeholder_uni_addr_pres } uni_addr_pres ;

/* Variables and functions */
#define  UNI_ADDR_NONUMBER 134 
#define  UNI_ADDR_PRES 133 
#define  UNI_ADDR_RESTRICT 132 
#define  UNI_ADDR_SCREEN_FAILED 131 
#define  UNI_ADDR_SCREEN_NET 130 
#define  UNI_ADDR_SCREEN_NOT 129 
#define  UNI_ADDR_SCREEN_PASSED 128 

__attribute__((used)) static int
check_screen(enum uni_addr_screen screen, enum uni_addr_pres pres)
{
	switch(pres) {
	  default:
		return -1;

	  case UNI_ADDR_PRES:
	  case UNI_ADDR_RESTRICT:
	  case UNI_ADDR_NONUMBER:
		break;
	}
	switch(screen) {
	  default:
		return -1;

	  case UNI_ADDR_SCREEN_NOT:
	  case UNI_ADDR_SCREEN_PASSED:
	  case UNI_ADDR_SCREEN_FAILED:
	  case UNI_ADDR_SCREEN_NET:
		break;
	}

	return 0;
}