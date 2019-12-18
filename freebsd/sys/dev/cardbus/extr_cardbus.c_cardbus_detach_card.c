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
 int /*<<< orphan*/  POWER_DISABLE_SOCKET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 int device_delete_children (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cardbus_detach_card(device_t cbdev)
{
	int err = 0;

	err = bus_generic_detach(cbdev);
	if (err)
		return (err);
	err = device_delete_children(cbdev);
	if (err)
		return (err);

	POWER_DISABLE_SOCKET(device_get_parent(cbdev), cbdev);
	return (err);
}