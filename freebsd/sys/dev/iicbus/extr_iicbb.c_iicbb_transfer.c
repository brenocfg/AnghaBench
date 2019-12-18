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
struct iic_msg {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  IICBB_POST_XFER (int /*<<< orphan*/ ) ; 
 int IICBB_PRE_XFER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int iicbus_transfer_gen (int /*<<< orphan*/ ,struct iic_msg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iicbb_transfer(device_t dev, struct iic_msg *msgs, uint32_t nmsgs)
{
	int error;

	error = IICBB_PRE_XFER(device_get_parent(dev));
	if (error)
		return (error);

	error = iicbus_transfer_gen(dev, msgs, nmsgs);

	IICBB_POST_XFER(device_get_parent(dev));
	return (error);
}