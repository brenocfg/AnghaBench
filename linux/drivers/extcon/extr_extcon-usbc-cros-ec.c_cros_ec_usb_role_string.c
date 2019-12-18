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

/* Variables and functions */
 unsigned int DR_HOST ; 
 unsigned int DR_NONE ; 

__attribute__((used)) static const char *cros_ec_usb_role_string(unsigned int role)
{
	return role == DR_NONE ? "DISCONNECTED" :
		(role == DR_HOST ? "DFP" : "UFP");
}