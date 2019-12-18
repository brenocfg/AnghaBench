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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int SCL_out ; 
 scalar_t__ SDA_out ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_assert_locked (int /*<<< orphan*/ ) ; 
 int ppb_rctr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_wctr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_wdtr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpbb_reset_bus(device_t dev)
{
	device_t ppbus = device_get_parent(dev);

	ppb_assert_locked(ppbus);
	ppb_wdtr(ppbus, (u_char)~SDA_out);
	ppb_wctr(ppbus, (u_char)(ppb_rctr(ppbus) | SCL_out));
}