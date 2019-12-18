#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct uio {scalar_t__ uio_rw; } ;
struct iic_cdevpriv {int addr; TYPE_1__* sc; scalar_t__ started; } ;
struct cdev {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int ENXIO ; 
 int IIC_DONTWAIT ; 
 int IIC_INTR ; 
 int /*<<< orphan*/  IIC_LAST_READ ; 
 int /*<<< orphan*/  IIC_LOCK (struct iic_cdevpriv*) ; 
 int /*<<< orphan*/  IIC_UNLOCK (struct iic_cdevpriv*) ; 
 int IIC_WAIT ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int LSB ; 
 int O_NONBLOCK ; 
 scalar_t__ UIO_READ ; 
 int devfs_get_cdevpriv (void**) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iicbus_release_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iicbus_request_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int iicbus_start (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iicbus_stop (int /*<<< orphan*/ ) ; 
 int iicuio_move (struct iic_cdevpriv*,struct uio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iicuio(struct cdev *dev, struct uio *uio, int ioflag)
{
	device_t parent;
	struct iic_cdevpriv *priv;
	int error;
	uint8_t addr;

	priv = NULL;
	error = devfs_get_cdevpriv((void**)&priv);

	if (error != 0)
		return (error);
	KASSERT(priv != NULL, ("iic cdevpriv should not be NULL!"));

	IIC_LOCK(priv);
	if (priv->started || (priv->addr == 0)) {
		IIC_UNLOCK(priv);
		return (ENXIO);
	}
	parent = device_get_parent(priv->sc->sc_dev);

	error = iicbus_request_bus(parent, priv->sc->sc_dev,
	    (ioflag & O_NONBLOCK) ? IIC_DONTWAIT : (IIC_WAIT | IIC_INTR));
	if (error != 0) {
		IIC_UNLOCK(priv);
		return (error);
	}

	if (uio->uio_rw == UIO_READ)
		addr = priv->addr | LSB;
	else
		addr = priv->addr & ~LSB;

	error = iicbus_start(parent, addr, 0);
	if (error != 0)
	{
		iicbus_release_bus(parent, priv->sc->sc_dev);
		IIC_UNLOCK(priv);
		return (error);
	}

	error = iicuio_move(priv, uio, IIC_LAST_READ);

	iicbus_stop(parent);
	iicbus_release_bus(parent, priv->sc->sc_dev);
	IIC_UNLOCK(priv);
	return (error);
}