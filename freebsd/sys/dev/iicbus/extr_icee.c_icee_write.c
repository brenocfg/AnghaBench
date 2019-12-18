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
struct uio {int uio_offset; int /*<<< orphan*/  uio_resid; } ;
struct iic_msg {int member_2; int* member_3; int len; int slave; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct icee_softc {int size; int type; int wr_sz; int addr; int /*<<< orphan*/  dev; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 struct icee_softc* CDEV2SOFTC (struct cdev*) ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  IIC_INTRWAIT ; 
 int /*<<< orphan*/  IIC_M_RD ; 
 int /*<<< orphan*/  IIC_M_WR ; 
 int /*<<< orphan*/  MAX_WR_SZ ; 
 int MIN (int,int /*<<< orphan*/ ) ; 
 int iic2errno (int) ; 
 int iicbus_transfer_excl (int /*<<< orphan*/ ,struct iic_msg*,int,int /*<<< orphan*/ ) ; 
 int uiomove (int*,int,struct uio*) ; 

__attribute__((used)) static int
icee_write(struct cdev *dev, struct uio *uio, int ioflag)
{
	struct icee_softc *sc;
	int error, len, slave, waitlimit;
	uint8_t data[MAX_WR_SZ + 2];
	struct iic_msg wr[1] = {
	     { 0, IIC_M_WR, 0, data },
	};
	struct iic_msg rd[1] = {
	     { 0, IIC_M_RD, 1, data },
	};

	sc = CDEV2SOFTC(dev);
	if (uio->uio_offset >= sc->size)
		return (EIO);
	if (sc->type != 8 && sc->type != 16)
		return (EINVAL);

	slave = error = 0;
	while (uio->uio_resid > 0) {
		if (uio->uio_offset >= sc->size)
			break;
		len = MIN(sc->wr_sz - (uio->uio_offset & (sc->wr_sz - 1)),
		    uio->uio_resid);
		switch (sc->type) {
		case 8:
			slave = (uio->uio_offset >> 7) | sc->addr;
			wr[0].len = 1 + len;
			data[0] = uio->uio_offset & 0xff;
			break;
		case 16:
			slave = sc->addr | (uio->uio_offset >> 15);
			wr[0].len = 2 + len;
			data[0] = (uio->uio_offset >> 8) & 0xff;
			data[1] = uio->uio_offset & 0xff;
			break;
		}
		wr[0].slave = slave;
		error = uiomove(data + sc->type / 8, len, uio);
		if (error)
			break;
		error = iicbus_transfer_excl(sc->dev, wr, 1, IIC_INTRWAIT);
		if (error) {
			error = iic2errno(error);
			break;
		}
		/* Read after write to wait for write-done. */
		waitlimit = 10000;
		rd[0].slave = slave;
		do {
			error = iicbus_transfer_excl(sc->dev, rd, 1,
			    IIC_INTRWAIT);
		} while (waitlimit-- > 0 && error != 0);
		if (error) {
			error = iic2errno(error);
			break;
		}
	}
	return error;
}