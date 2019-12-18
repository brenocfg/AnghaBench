#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bxe_softc {TYPE_1__* ioctl_dev; int /*<<< orphan*/ * eeprom; TYPE_2__* ifp; } ;
struct TYPE_4__ {int /*<<< orphan*/  if_dunit; } ;
struct TYPE_3__ {struct bxe_softc* si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGW (struct bxe_softc*,char*) ; 
 int /*<<< orphan*/  BXE_EEPROM_MAX_DATA_LEN ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  bxe_cdevsw ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_name (TYPE_2__*) ; 
 TYPE_1__* make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bxe_add_cdev(struct bxe_softc *sc)
{
    sc->eeprom = malloc(BXE_EEPROM_MAX_DATA_LEN, M_DEVBUF, M_NOWAIT);

    if (sc->eeprom == NULL) {
        BLOGW(sc, "Unable to alloc for eeprom size buffer\n");
        return (-1);
    }

    sc->ioctl_dev = make_dev(&bxe_cdevsw,
                            sc->ifp->if_dunit,
                            UID_ROOT,
                            GID_WHEEL,
                            0600,
                            "%s",
                            if_name(sc->ifp));

    if (sc->ioctl_dev == NULL) {
        free(sc->eeprom, M_DEVBUF);
        sc->eeprom = NULL;
        return (-1);
    }

    sc->ioctl_dev->si_drv1 = sc;

    return (0);
}