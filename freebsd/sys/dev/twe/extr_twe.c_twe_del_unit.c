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
struct twe_softc {TYPE_1__* twe_drive; } ;
struct TYPE_2__ {int /*<<< orphan*/ * td_disk; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  TWE_CONFIG_ASSERT_LOCKED (struct twe_softc*) ; 
 int TWE_MAX_UNITS ; 
 int twe_detach_drive (struct twe_softc*,int) ; 

__attribute__((used)) static int
twe_del_unit(struct twe_softc *sc, int unit)
{
    int error;

    TWE_CONFIG_ASSERT_LOCKED(sc);
    if (unit < 0 || unit >= TWE_MAX_UNITS)
	return (ENXIO);

    if (sc->twe_drive[unit].td_disk == NULL)
	return (ENXIO);

    error = twe_detach_drive(sc, unit);
    return (error);
}