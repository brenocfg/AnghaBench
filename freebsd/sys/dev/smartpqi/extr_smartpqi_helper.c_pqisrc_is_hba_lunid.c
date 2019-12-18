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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 scalar_t__ RAID_CTLR_LUNID ; 
 int /*<<< orphan*/  pqisrc_scsi3addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

boolean_t pqisrc_is_hba_lunid(uint8_t *scsi3addr)
{
	return pqisrc_scsi3addr_equal(scsi3addr, (uint8_t*)RAID_CTLR_LUNID);
}