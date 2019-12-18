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
struct ppb_data {int mode; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 struct ppb_data* DEVTOSOFTC (int /*<<< orphan*/ ) ; 
 scalar_t__ PPBUS_SETMODE (int /*<<< orphan*/ ,int) ; 
 int PPB_MASK ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppb_assert_locked (int /*<<< orphan*/ ) ; 
 int ppb_get_mode (int /*<<< orphan*/ ) ; 

int
ppb_set_mode(device_t bus, int mode)
{
	struct ppb_data *ppb = DEVTOSOFTC(bus);
	int old_mode = ppb_get_mode(bus);

	ppb_assert_locked(bus);
	if (PPBUS_SETMODE(device_get_parent(bus), mode))
		return (-1);

	/* XXX yet device mode = ppbus mode = chipset mode */
	ppb->mode = (mode & PPB_MASK);

	return (old_mode);
}