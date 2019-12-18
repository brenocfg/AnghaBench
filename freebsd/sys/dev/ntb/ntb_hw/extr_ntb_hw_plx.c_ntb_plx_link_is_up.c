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
typedef  int uint16_t ;
typedef  enum ntb_width { ____Placeholder_ntb_width } ntb_width ;
typedef  enum ntb_speed { ____Placeholder_ntb_speed } ntb_speed ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCIEM_LINK_STA_SPEED ; 
 int PCIEM_LINK_STA_WIDTH ; 
 int /*<<< orphan*/  PCIER_LINK_STA ; 
 int pcie_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
ntb_plx_link_is_up(device_t dev, enum ntb_speed *speed, enum ntb_width *width)
{
	uint16_t link;

	link = pcie_read_config(dev, PCIER_LINK_STA, 2);
	if (speed != NULL)
		*speed = (link & PCIEM_LINK_STA_SPEED);
	if (width != NULL)
		*width = (link & PCIEM_LINK_STA_WIDTH) >> 4;
	return ((link & PCIEM_LINK_STA_WIDTH) != 0);
}