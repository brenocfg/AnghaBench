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
typedef  int uint32_t ;
struct iic_msg {int slave; int flags; int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IIC_ENOTSUPP ; 
 int IIC_ERESOURCE ; 
 int /*<<< orphan*/  IIC_LAST_READ ; 
 int IIC_M_NOSTART ; 
 int IIC_M_NOSTOP ; 
 int IIC_M_RD ; 
 int LSB ; 
 int /*<<< orphan*/  M_TEMP ; 
 int device_get_children (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int iicbus_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iicbus_repeated_start (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int iicbus_start (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iicbus_stop (int /*<<< orphan*/ ) ; 
 int iicbus_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

int
iicbus_transfer_gen(device_t dev, struct iic_msg *msgs, uint32_t nmsgs)
{
	int i, error, lenread, lenwrote, nkid, rpstart, addr;
	device_t *children, bus;
	bool started;

	if ((error = device_get_children(dev, &children, &nkid)) != 0)
		return (IIC_ERESOURCE);
	if (nkid != 1) {
		free(children, M_TEMP);
		return (IIC_ENOTSUPP);
	}
	bus = children[0];
	rpstart = 0;
	free(children, M_TEMP);
	started = false;
	for (i = 0, error = 0; i < nmsgs && error == 0; i++) {
		addr = msgs[i].slave;
		if (msgs[i].flags & IIC_M_RD)
			addr |= LSB;
		else
			addr &= ~LSB;

		if (!(msgs[i].flags & IIC_M_NOSTART)) {
			if (rpstart)
				error = iicbus_repeated_start(bus, addr, 0);
			else
				error = iicbus_start(bus, addr, 0);
			if (error != 0)
				break;
			started = true;
		}

		if (msgs[i].flags & IIC_M_RD)
			error = iicbus_read(bus, msgs[i].buf, msgs[i].len,
			    &lenread, IIC_LAST_READ, 0);
		else
			error = iicbus_write(bus, msgs[i].buf, msgs[i].len,
			    &lenwrote, 0);
		if (error != 0)
			break;

		if (!(msgs[i].flags & IIC_M_NOSTOP)) {
			rpstart = 0;
			iicbus_stop(bus);
		} else {
			rpstart = 1;	/* Next message gets repeated start */
		}
	}
	if (error != 0 && started)
		iicbus_stop(bus);
	return (error);
}