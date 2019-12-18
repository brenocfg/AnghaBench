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
struct twe_softc {int /*<<< orphan*/  twe_dev; } ;
struct twe_drive {int td_twe_unit; int td_type; int td_state; int /*<<< orphan*/ * td_disk; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  Giant ; 
 int TWE_PARAM_UNITSTATUS_MASK ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int device_probe_and_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct twe_drive*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,char*,char*) ; 
 char* twe_describe_code (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  twe_printf (struct twe_softc*,char*,...) ; 
 int /*<<< orphan*/  twe_table_unitstate ; 
 int /*<<< orphan*/  twe_table_unittype ; 

int
twe_attach_drive(struct twe_softc *sc, struct twe_drive *dr)
{
    char	buf[80];
    int		error;

    mtx_lock(&Giant);
    dr->td_disk =  device_add_child(sc->twe_dev, NULL, -1);
    if (dr->td_disk == NULL) {
	mtx_unlock(&Giant);
	twe_printf(sc, "Cannot add unit\n");
	return (EIO);
    }
    device_set_ivars(dr->td_disk, dr);

    /* 
     * XXX It would make sense to test the online/initialising bits, but they seem to be
     * always set...
     */
    sprintf(buf, "Unit %d, %s, %s",
	    dr->td_twe_unit,
	    twe_describe_code(twe_table_unittype, dr->td_type),
	    twe_describe_code(twe_table_unitstate, dr->td_state & TWE_PARAM_UNITSTATUS_MASK));
    device_set_desc_copy(dr->td_disk, buf);

    error = device_probe_and_attach(dr->td_disk);
    mtx_unlock(&Giant);
    if (error != 0) {
	twe_printf(sc, "Cannot attach unit to controller. error = %d\n", error);
	return (EIO);
    }
    return (0);
}