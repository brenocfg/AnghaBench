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
typedef  int /*<<< orphan*/  uint16_t ;
struct bwi_mac {int dummy; } ;
typedef  scalar_t__ int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  BWI_PHYR_NRSSI_CTRL ; 
 int /*<<< orphan*/  BWI_PHYR_NRSSI_DATA ; 
 int /*<<< orphan*/  PHY_WRITE (struct bwi_mac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bwi_nrssi_write(struct bwi_mac *mac, uint16_t ofs, int16_t data)
{
	PHY_WRITE(mac, BWI_PHYR_NRSSI_CTRL, ofs);
	PHY_WRITE(mac, BWI_PHYR_NRSSI_DATA, (uint16_t)data);
}