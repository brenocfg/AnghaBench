#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int16_t ;
struct twe_softc {struct twe_drive* twe_drive; } ;
struct twe_drive {int td_size; int td_heads; int td_sectors; int td_cylinders; int td_twe_unit; int /*<<< orphan*/  td_stripe; int /*<<< orphan*/  td_type; int /*<<< orphan*/  td_state; } ;
struct TYPE_6__ {int /*<<< orphan*/  stripe_size; int /*<<< orphan*/  configuration; } ;
struct TYPE_5__ {int* data; } ;
typedef  TYPE_1__ TWE_Param ;
typedef  TYPE_2__ TWE_Array_Descriptor ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENXIO ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  TWE_CONFIG_ASSERT_LOCKED (struct twe_softc*) ; 
 int /*<<< orphan*/  TWE_IO_LOCK (struct twe_softc*) ; 
 int /*<<< orphan*/  TWE_IO_UNLOCK (struct twe_softc*) ; 
 int TWE_MAX_UNITS ; 
 int TWE_PARAM_UNITINFO ; 
 int /*<<< orphan*/  TWE_PARAM_UNITINFO_Capacity ; 
 int /*<<< orphan*/  TWE_PARAM_UNITINFO_Descriptor ; 
 int /*<<< orphan*/  TWE_PARAM_UNITINFO_DescriptorSize ; 
 int /*<<< orphan*/  TWE_PARAM_UNITINFO_Status ; 
 int TWE_PARAM_UNITSTATUS_Online ; 
 int TWE_PARAM_UNITSUMMARY ; 
 int /*<<< orphan*/  TWE_PARAM_UNITSUMMARY_Status ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int twe_attach_drive (struct twe_softc*,struct twe_drive*) ; 
 TYPE_1__* twe_get_param (struct twe_softc*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ twe_get_param_1 (struct twe_softc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ twe_get_param_2 (struct twe_softc*,int,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ twe_get_param_4 (struct twe_softc*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  twe_printf (struct twe_softc*,char*,...) ; 

__attribute__((used)) static int
twe_add_unit(struct twe_softc *sc, int unit)
{
    struct twe_drive		*dr;
    int				table, error = 0;
    u_int16_t			dsize;
    TWE_Param			*drives = NULL, *param = NULL;
    TWE_Array_Descriptor	*ud;

    TWE_CONFIG_ASSERT_LOCKED(sc);
    if (unit < 0 || unit > TWE_MAX_UNITS)
	return (EINVAL);

    /*
     * The controller is in a safe state, so try to find drives attached to it.
     */
    TWE_IO_LOCK(sc);
    if ((drives = twe_get_param(sc, TWE_PARAM_UNITSUMMARY, TWE_PARAM_UNITSUMMARY_Status,
				TWE_MAX_UNITS, NULL)) == NULL) {
	TWE_IO_UNLOCK(sc);
	twe_printf(sc, "can't detect attached units\n");
	return (EIO);
    }

    dr = &sc->twe_drive[unit];
    /* check that the drive is online */
    if (!(drives->data[unit] & TWE_PARAM_UNITSTATUS_Online)) {
	TWE_IO_UNLOCK(sc);
	error = ENXIO;
	goto out;
    }

    table = TWE_PARAM_UNITINFO + unit;

    if (twe_get_param_4(sc, table, TWE_PARAM_UNITINFO_Capacity, &dr->td_size)) {
	TWE_IO_UNLOCK(sc);
	twe_printf(sc, "error fetching capacity for unit %d\n", unit);
	error = EIO;
	goto out;
    }
    if (twe_get_param_1(sc, table, TWE_PARAM_UNITINFO_Status, &dr->td_state)) {
	TWE_IO_UNLOCK(sc);
	twe_printf(sc, "error fetching state for unit %d\n", unit);
	error = EIO;
	goto out;
    }
    if (twe_get_param_2(sc, table, TWE_PARAM_UNITINFO_DescriptorSize, &dsize)) {
	TWE_IO_UNLOCK(sc);
	twe_printf(sc, "error fetching descriptor size for unit %d\n", unit);
	error = EIO;
	goto out;
    }
    if ((param = twe_get_param(sc, table, TWE_PARAM_UNITINFO_Descriptor, dsize - 3, NULL)) == NULL) {
	TWE_IO_UNLOCK(sc);
	twe_printf(sc, "error fetching descriptor for unit %d\n", unit);
	error = EIO;
	goto out;
    }
    ud = (TWE_Array_Descriptor *)param->data;
    dr->td_type = ud->configuration;
    dr->td_stripe = ud->stripe_size;

    /* build synthetic geometry as per controller internal rules */
    if (dr->td_size > 0x200000) {
	dr->td_heads = 255;
	dr->td_sectors = 63;
    } else {
	dr->td_heads = 64;
	dr->td_sectors = 32;
    }
    dr->td_cylinders = dr->td_size / (dr->td_heads * dr->td_sectors);
    dr->td_twe_unit = unit;
    TWE_IO_UNLOCK(sc);

    error = twe_attach_drive(sc, dr);

out:
    if (param != NULL)
	free(param, M_DEVBUF);
    if (drives != NULL)
	free(drives, M_DEVBUF);
    return (error);
}