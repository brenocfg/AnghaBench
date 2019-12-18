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
struct disk {TYPE_1__* d_drv1; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ ipsdisk_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_PRINTF (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IPS_DEV_OPEN ; 

__attribute__((used)) static int ipsd_open(struct disk *dp)
{
	ipsdisk_softc_t *dsc = dp->d_drv1;

	dsc->state |= IPS_DEV_OPEN;
	DEVICE_PRINTF(2, dsc->dev, "I'm open\n");
       	return 0;
}