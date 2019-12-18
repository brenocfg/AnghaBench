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
struct ppb_xfer {struct ppb_microseq* loop; } ;
struct ppb_microseq {int dummy; } ;
struct ppb_device {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ device_get_ivars (int /*<<< orphan*/ ) ; 
 struct ppb_xfer* mode2xfer (int /*<<< orphan*/ ,struct ppb_device*,int) ; 
 int /*<<< orphan*/  ppb_assert_locked (int /*<<< orphan*/ ) ; 

int
ppb_MS_init(device_t bus, device_t dev, struct ppb_microseq *loop, int opcode)
{
	struct ppb_device *ppbdev = (struct ppb_device *)device_get_ivars(dev);
	struct ppb_xfer *xfer = mode2xfer(bus, ppbdev, opcode);

	ppb_assert_locked(bus);
	xfer->loop = loop;

	return (0);
}