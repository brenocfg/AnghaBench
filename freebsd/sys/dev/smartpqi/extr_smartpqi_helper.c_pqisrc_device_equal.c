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
struct TYPE_4__ {scalar_t__ wwid; } ;
typedef  TYPE_1__ pqi_scsi_dev_t ;
typedef  int boolean_t ;

/* Variables and functions */

boolean_t pqisrc_device_equal(pqi_scsi_dev_t *dev1,
	pqi_scsi_dev_t *dev2)
{
	return dev1->wwid == dev2->wwid;
}