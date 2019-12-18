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
typedef  int u16 ;

/* Variables and functions */
 int WPS_CONFIG_PHY_PUSHBUTTON ; 
 int WPS_CONFIG_PUSHBUTTON ; 
 int WPS_CONFIG_VIRT_PUSHBUTTON ; 

__attribute__((used)) static void wps_set_pushbutton(u16 *methods, u16 conf_methods)
{
	*methods |= WPS_CONFIG_PUSHBUTTON;
	if ((conf_methods & WPS_CONFIG_VIRT_PUSHBUTTON) ==
	    WPS_CONFIG_VIRT_PUSHBUTTON)
		*methods |= WPS_CONFIG_VIRT_PUSHBUTTON;
	if ((conf_methods & WPS_CONFIG_PHY_PUSHBUTTON) ==
	    WPS_CONFIG_PHY_PUSHBUTTON)
		*methods |= WPS_CONFIG_PHY_PUSHBUTTON;
	if ((*methods & WPS_CONFIG_VIRT_PUSHBUTTON) !=
	    WPS_CONFIG_VIRT_PUSHBUTTON &&
	    (*methods & WPS_CONFIG_PHY_PUSHBUTTON) !=
	    WPS_CONFIG_PHY_PUSHBUTTON) {
		/*
		 * Required to include virtual/physical flag, but we were not
		 * configured with push button type, so have to default to one
		 * of them.
		 */
		*methods |= WPS_CONFIG_PHY_PUSHBUTTON;
	}
}