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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  superio_dev_type_t ;
struct superio_devinfo {void* dma; void* irq; void* iobase2; void* iobase; int /*<<< orphan*/  type; int /*<<< orphan*/  ldn; } ;
struct siosc {int /*<<< orphan*/  devlist; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct superio_devinfo*,int /*<<< orphan*/ ) ; 
 struct superio_devinfo* device_get_ivars (int /*<<< orphan*/ *) ; 
 struct siosc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devtype_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  sio_conf_enter (struct siosc*) ; 
 int /*<<< orphan*/  sio_conf_exit (struct siosc*) ; 
 void* sio_ldn_readw (struct siosc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
superio_add_known_child(device_t dev, superio_dev_type_t type, uint8_t ldn)
{
	struct siosc *sc = device_get_softc(dev);
	struct superio_devinfo *dinfo;
	device_t child;

	child = BUS_ADD_CHILD(dev, 0, NULL, -1);
	if (child == NULL) {
		device_printf(dev, "failed to add child for ldn %d, type %s\n",
		    ldn, devtype_to_str(type));
		return;
	}
	dinfo = device_get_ivars(child);
	dinfo->ldn = ldn;
	dinfo->type = type;
	sio_conf_enter(sc);
	dinfo->iobase = sio_ldn_readw(sc, ldn, 0x60);
	dinfo->iobase2 = sio_ldn_readw(sc, ldn, 0x62);
	dinfo->irq = sio_ldn_readw(sc, ldn, 0x70);
	dinfo->dma = sio_ldn_readw(sc, ldn, 0x74);
	sio_conf_exit(sc);
	STAILQ_INSERT_TAIL(&sc->devlist, dinfo, link);
}