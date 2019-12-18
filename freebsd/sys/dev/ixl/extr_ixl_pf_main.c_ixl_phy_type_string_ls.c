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
 char* ixl_phy_type_string (int,int) ; 

__attribute__((used)) static char *
ixl_phy_type_string_ls(u8 val)
{
	if (val >= 0x1F)
		return ixl_phy_type_string(val - 0x1F, true);
	else
		return ixl_phy_type_string(val, false);
}