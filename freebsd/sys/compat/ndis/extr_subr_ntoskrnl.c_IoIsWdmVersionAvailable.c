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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 scalar_t__ WDM_MAJOR ; 
 scalar_t__ WDM_MINOR_WINXP ; 

__attribute__((used)) static uint8_t
IoIsWdmVersionAvailable(uint8_t major, uint8_t minor)
{
	if (major == WDM_MAJOR && minor == WDM_MINOR_WINXP)
		return (TRUE);
	return (FALSE);
}