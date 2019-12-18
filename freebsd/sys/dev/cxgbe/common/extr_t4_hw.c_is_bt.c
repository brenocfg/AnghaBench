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
struct port_info {scalar_t__ port_type; } ;

/* Variables and functions */
 scalar_t__ FW_PORT_TYPE_BT_SGMII ; 
 scalar_t__ FW_PORT_TYPE_BT_XAUI ; 
 scalar_t__ FW_PORT_TYPE_BT_XFI ; 

__attribute__((used)) static bool
is_bt(struct port_info *pi)
{

	return (pi->port_type == FW_PORT_TYPE_BT_SGMII ||
	    pi->port_type == FW_PORT_TYPE_BT_XFI ||
	    pi->port_type == FW_PORT_TYPE_BT_XAUI);
}