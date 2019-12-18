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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int /*<<< orphan*/  MBOX_WRITE (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devclass_find (char*) ; 
 scalar_t__ devclass_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bcm_mbox_write(int channel, uint32_t data)
{
	device_t mbox;

        mbox = devclass_get_device(devclass_find("mbox"), 0);

        if (mbox)
                MBOX_WRITE(mbox, channel, data);
}