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
typedef  int uint8_t ;
struct usb_device {int /*<<< orphan*/  sr_sx; int /*<<< orphan*/  enum_sx; } ;

/* Variables and functions */
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 scalar_t__ sx_xlocked (int /*<<< orphan*/ *) ; 

uint8_t
usbd_enum_lock(struct usb_device *udev)
{
	if (sx_xlocked(&udev->enum_sx))
		return (0);

	sx_xlock(&udev->enum_sx);
	sx_xlock(&udev->sr_sx);
	/* 
	 * NEWBUS LOCK NOTE: We should check if any parent SX locks
	 * are locked before locking Giant. Else the lock can be
	 * locked multiple times.
	 */
	mtx_lock(&Giant);
	return (1);
}