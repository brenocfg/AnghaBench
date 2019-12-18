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
typedef  int PortControl ;

/* Variables and functions */
#define  Auto 130 
#define  ForceAuthorized 129 
#define  ForceUnauthorized 128 

__attribute__((used)) static const char * eapol_port_control(PortControl ctrl)
{
	switch (ctrl) {
	case Auto:
		return "Auto";
	case ForceUnauthorized:
		return "ForceUnauthorized";
	case ForceAuthorized:
		return "ForceAuthorized";
	default:
		return "Unknown";
	}
}