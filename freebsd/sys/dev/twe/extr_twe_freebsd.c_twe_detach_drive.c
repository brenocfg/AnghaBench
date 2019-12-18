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
struct twe_softc {TYPE_1__* twe_drive; int /*<<< orphan*/  twe_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  td_disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  TWE_CONFIG_ASSERT_LOCKED (struct twe_softc*) ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  twe_printf (struct twe_softc*,char*,int) ; 

int
twe_detach_drive(struct twe_softc *sc, int unit)
{
    int error = 0;

    TWE_CONFIG_ASSERT_LOCKED(sc);
    mtx_lock(&Giant);
    error = device_delete_child(sc->twe_dev, sc->twe_drive[unit].td_disk);
    mtx_unlock(&Giant);
    if (error != 0) {
	twe_printf(sc, "failed to delete unit %d\n", unit);
	return(error);
    }
    bzero(&sc->twe_drive[unit], sizeof(sc->twe_drive[unit]));
    return(error);
}