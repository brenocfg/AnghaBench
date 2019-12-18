#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cryp_device_data {TYPE_1__* base; } ;
struct TYPE_2__ {int /*<<< orphan*/  pcellId3; int /*<<< orphan*/  pcellId2; int /*<<< orphan*/  pcellId1; int /*<<< orphan*/  pcellId0; int /*<<< orphan*/  periphId3; int /*<<< orphan*/  periphId1; int /*<<< orphan*/  periphId0; int /*<<< orphan*/  periphId2; } ;

/* Variables and functions */
 int CRYP_PCELL_ID0 ; 
 int CRYP_PCELL_ID1 ; 
 int CRYP_PCELL_ID2 ; 
 int CRYP_PCELL_ID3 ; 
 int CRYP_PERIPHERAL_ID0 ; 
 int CRYP_PERIPHERAL_ID1 ; 
 int CRYP_PERIPHERAL_ID2_DB8500 ; 
 int CRYP_PERIPHERAL_ID3 ; 
 int EINVAL ; 
 int EPERM ; 
 int readl_relaxed (int /*<<< orphan*/ *) ; 

int cryp_check(struct cryp_device_data *device_data)
{
	int peripheralid2 = 0;

	if (NULL == device_data)
		return -EINVAL;

	peripheralid2 = readl_relaxed(&device_data->base->periphId2);

	if (peripheralid2 != CRYP_PERIPHERAL_ID2_DB8500)
		return -EPERM;

	/* Check Peripheral and Pcell Id Register for CRYP */
	if ((CRYP_PERIPHERAL_ID0 ==
		readl_relaxed(&device_data->base->periphId0))
	    && (CRYP_PERIPHERAL_ID1 ==
		    readl_relaxed(&device_data->base->periphId1))
	    && (CRYP_PERIPHERAL_ID3 ==
		    readl_relaxed(&device_data->base->periphId3))
	    && (CRYP_PCELL_ID0 ==
		    readl_relaxed(&device_data->base->pcellId0))
	    && (CRYP_PCELL_ID1 ==
		    readl_relaxed(&device_data->base->pcellId1))
	    && (CRYP_PCELL_ID2 ==
		    readl_relaxed(&device_data->base->pcellId2))
	    && (CRYP_PCELL_ID3 ==
		    readl_relaxed(&device_data->base->pcellId3))) {
		return 0;
	}

	return -EPERM;
}