#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int dwSize; int SupportSparePool; int* SupportedRAIDTypes; int* MaximumArrayMembers; scalar_t__ SupportDedicatedSpare; scalar_t__ MaximumArrayNameLength; scalar_t__ SupportDiskModeSetting; int /*<<< orphan*/  MaximumBlockSizeShift; int /*<<< orphan*/  MinimumBlockSizeShift; scalar_t__ SupportCrossControllerRAID; int /*<<< orphan*/  MaximumControllers; } ;
typedef  TYPE_1__* PDRIVER_CAPABILITIES ;
typedef  int /*<<< orphan*/  DRIVER_CAPABILITIES ;

/* Variables and functions */
 int AT_JBOD ; 
 int AT_RAID0 ; 
 int AT_RAID1 ; 
 int AT_RAID5 ; 
 scalar_t__ MAX_ARRAY_NAME ; 
 void* MAX_MEMBERS ; 
 int /*<<< orphan*/  MAX_VBUS ; 
 int /*<<< orphan*/  MaxBlockSizeShift ; 
 int /*<<< orphan*/  MinBlockSizeShift ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 

int hpt_get_driver_capabilities(PDRIVER_CAPABILITIES cap)
{
	ZeroMemory(cap, sizeof(DRIVER_CAPABILITIES));
	cap->dwSize = sizeof(DRIVER_CAPABILITIES);
	cap->MaximumControllers = MAX_VBUS;

	/* cap->SupportCrossControllerRAID = 0; */
	/* take care for various OSes! */
	cap->SupportCrossControllerRAID = 0;


	cap->MinimumBlockSizeShift = MinBlockSizeShift;
	cap->MaximumBlockSizeShift = MaxBlockSizeShift;
	cap->SupportDiskModeSetting = 0;
	cap->SupportSparePool = 1;		
	cap->MaximumArrayNameLength = MAX_ARRAY_NAME - 1;
	cap->SupportDedicatedSpare = 0;
	

#ifdef SUPPORT_ARRAY
	/* Stripe */
	cap->SupportedRAIDTypes[0] = AT_RAID0;
	cap->MaximumArrayMembers[0] = MAX_MEMBERS;
	/* Mirror */
	cap->SupportedRAIDTypes[1] = AT_RAID1;
	cap->MaximumArrayMembers[1] = 2;
	/* Mirror + Stripe */
#ifdef ARRAY_V2_ONLY
	cap->SupportedRAIDTypes[2] = (AT_RAID1<<4)|AT_RAID0; /* RAID0/1 */
#else 
	cap->SupportedRAIDTypes[2] = (AT_RAID0<<4)|AT_RAID1; /* RAID1/0 */
#endif
	cap->MaximumArrayMembers[2] = MAX_MEMBERS;
	/* Jbod */
	cap->SupportedRAIDTypes[3] = AT_JBOD;
	cap->MaximumArrayMembers[3] = MAX_MEMBERS;
	/* RAID5 */
#if SUPPORT_RAID5
	cap->SupportedRAIDTypes[4] = AT_RAID5;
	cap->MaximumArrayMembers[4] = MAX_MEMBERS;
#endif
#endif
	return 0;
}