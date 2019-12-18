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
 int SDA_in ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_lock (int /*<<< orphan*/ ) ; 
 int ppb_rstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpbb_getsda(device_t dev)
{
	device_t ppbus = device_get_parent(dev);
	int rval;

	ppb_lock(ppbus);
	rval = ((ppb_rstr(ppbus) & SDA_in) == SDA_in);
	ppb_unlock(ppbus);
	return (rval);
}