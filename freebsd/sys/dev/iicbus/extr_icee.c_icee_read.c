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
struct uio {scalar_t__ uio_offset; scalar_t__ uio_resid; } ;
struct iic_msg {int member_2; int* member_3; int len; int slave; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct icee_softc {scalar_t__ size; int type; int addr; int /*<<< orphan*/  dev; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 struct icee_softc* CDEV2SOFTC (struct cdev*) ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  IIC_INTRWAIT ; 
 int /*<<< orphan*/  IIC_M_RD ; 
 int /*<<< orphan*/  IIC_M_WR ; 
 int MAX_RD_SZ ; 
 int MIN (int,scalar_t__) ; 
 int iic2errno (int) ; 
 int iicbus_transfer_excl (int /*<<< orphan*/ ,struct iic_msg*,int,int /*<<< orphan*/ ) ; 
 int uiomove (int*,int,struct uio*) ; 

__attribute__((used)) static int
icee_read(struct cdev *dev, struct uio *uio, int ioflag)
{
	struct icee_softc *sc;
	uint8_t addr[2];
	uint8_t data[MAX_RD_SZ];
	int error, i, len, slave;
	struct iic_msg msgs[2] = {
	     { 0, IIC_M_WR, 1, addr },
	     { 0, IIC_M_RD, 0, data },
	};

	sc = CDEV2SOFTC(dev);
	if (uio->uio_offset == sc->size)
		return (0);
	if (uio->uio_offset > sc->size)
		return (EIO);
	if (sc->type != 8 && sc->type != 16)
		return (EINVAL);
	slave = error = 0;
	while (uio->uio_resid > 0) {
		if (uio->uio_offset >= sc->size)
			break;
		len = MIN(MAX_RD_SZ - (uio->uio_offset & (MAX_RD_SZ - 1)),
		    uio->uio_resid);
		switch (sc->type) {
		case 8:
			slave = (uio->uio_offset >> 7) | sc->addr;
			msgs[0].len = 1;
			msgs[1].len = len;
			addr[0] = uio->uio_offset & 0xff;
			break;
		case 16:
			slave = sc->addr | (uio->uio_offset >> 15);
			msgs[0].len = 2;
			msgs[1].len = len;
			addr[0] = (uio->uio_offset >> 8) & 0xff;
			addr[1] = uio->uio_offset & 0xff;
			break;
		}
		for (i = 0; i < 2; i++)
			msgs[i].slave = slave;
		error = iicbus_transfer_excl(sc->dev, msgs, 2, IIC_INTRWAIT);
		if (error) {
			error = iic2errno(error);
			break;
		}
		error = uiomove(data, len, uio);
		if (error)
			break;
	}
	return (error);
}