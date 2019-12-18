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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  HDAC_PINDUMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_TEMP ; 
 scalar_t__ device_get_children (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hdacc_pindump(device_t dev)
{
	device_t *devlist;
	int devcount, i;

	if (device_get_children(dev, &devlist, &devcount) != 0)
		return;
	for (i = 0; i < devcount; i++)
		HDAC_PINDUMP(devlist[i]);
	free(devlist, M_TEMP);
}