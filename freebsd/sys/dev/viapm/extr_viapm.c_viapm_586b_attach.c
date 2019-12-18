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
struct viapm_softc {int /*<<< orphan*/  lock; scalar_t__ iores; int /*<<< orphan*/  iorid; int /*<<< orphan*/  iicbb; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  GPIO_DIR ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int VIAPM_INB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIAPM_OUTB (int /*<<< orphan*/ ,int) ; 
 int VIAPM_SCL ; 
 int VIAPM_SDA ; 
 scalar_t__ bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
viapm_586b_attach(device_t dev)
{
	struct viapm_softc *viapm = (struct viapm_softc *)device_get_softc(dev);

	mtx_init(&viapm->lock, device_get_nameunit(dev), "viapm", MTX_DEF);
	if (!(viapm->iores = bus_alloc_resource_any(dev, SYS_RES_IOPORT,
		&viapm->iorid, RF_ACTIVE | RF_SHAREABLE))) {
		device_printf(dev, "could not allocate bus resource\n");
		goto error;
	}

	VIAPM_OUTB(GPIO_DIR, VIAPM_INB(GPIO_DIR) | VIAPM_SCL | VIAPM_SDA);

	/* add generic bit-banging code */
	if (!(viapm->iicbb = device_add_child(dev, "iicbb", -1)))
		goto error;

	bus_generic_attach(dev);

	return 0;

error:
	if (viapm->iores)
		bus_release_resource(dev, SYS_RES_IOPORT,
					viapm->iorid, viapm->iores);
	mtx_destroy(&viapm->lock);
	return ENXIO;
}