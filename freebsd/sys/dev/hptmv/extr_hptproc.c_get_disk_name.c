#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_7__ {int /*<<< orphan*/ * ModelNumber; } ;
struct TYPE_6__ {scalar_t__ identifyDevice; } ;
struct TYPE_5__ {TYPE_2__* mv; } ;
typedef  TYPE_1__* PDevice ;
typedef  TYPE_2__ MV_SATA_CHANNEL ;
typedef  TYPE_3__ IDENTIFY_DATA2 ;

/* Variables and functions */
 int /*<<< orphan*/  shortswap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
get_disk_name(char *name, PDevice pDev)
{
	int i;
	MV_SATA_CHANNEL *pMvSataChannel = pDev->mv;
	IDENTIFY_DATA2 *pIdentifyData = (IDENTIFY_DATA2 *)pMvSataChannel->identifyDevice;
	
	for (i = 0; i < 10; i++) 
		((WORD*)name)[i] = shortswap(pIdentifyData->ModelNumber[i]);
	name[20] = '\0';
}