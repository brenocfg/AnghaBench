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
struct bxe_softc {int /*<<< orphan*/ * ioctl_dev; int /*<<< orphan*/ * eeprom; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bxe_del_cdev(struct bxe_softc *sc)
{
    if (sc->ioctl_dev != NULL)
        destroy_dev(sc->ioctl_dev);

    if (sc->eeprom != NULL) {
        free(sc->eeprom, M_DEVBUF);
        sc->eeprom = NULL;
    }
    sc->ioctl_dev = NULL;

    return;
}