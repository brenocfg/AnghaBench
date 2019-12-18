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
struct emu_sc_info {TYPE_1__* cdev; int /*<<< orphan*/  dev; int /*<<< orphan*/  emu10kx_lock; } ;
struct TYPE_2__ {struct emu_sc_info* si_drv1; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  PCMMINOR (int) ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emu10kx_cdevsw ; 
 TYPE_1__* make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
emu10kx_dev_init(struct emu_sc_info *sc)
{
	int unit;

	mtx_init(&sc->emu10kx_lock, device_get_nameunit(sc->dev), "kxdevlock", 0);
	unit = device_get_unit(sc->dev);

	sc->cdev = make_dev(&emu10kx_cdevsw, PCMMINOR(unit), UID_ROOT, GID_WHEEL, 0640, "emu10kx%d", unit);
	if (sc->cdev != NULL) {
		sc->cdev->si_drv1 = sc;
		return (0);
	}
	return (ENXIO);
}