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
typedef  enum ntb_width { ____Placeholder_ntb_width } ntb_width ;
typedef  enum ntb_speed { ____Placeholder_ntb_speed } ntb_speed ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int NTB_LINK_IS_UP (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

bool
ntb_link_is_up(device_t ntb, enum ntb_speed *speed, enum ntb_width *width)
{

	return (NTB_LINK_IS_UP(device_get_parent(ntb), speed, width));
}