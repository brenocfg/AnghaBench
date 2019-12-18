#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_8__ {int num_ports; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ e6000sw_softc_t ;

/* Variables and functions */
 scalar_t__ E6000SW_WAITREADY (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int EBUSY ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  REG_GLOBAL ; 
 int VTU_BUSY ; 
 int /*<<< orphan*/  VTU_DATA ; 
 int /*<<< orphan*/  VTU_DATA2 ; 
 int /*<<< orphan*/  VTU_FID ; 
 int VTU_FID_MASK (TYPE_1__*) ; 
 int VTU_LOAD ; 
 int /*<<< orphan*/  VTU_OPERATION ; 
 int VTU_PORT (TYPE_1__*,int) ; 
 int VTU_PORT_DISCARD ; 
 int VTU_PORT_TAGGED ; 
 int VTU_PORT_UNTAGGED ; 
 int VTU_PPREG (TYPE_1__*) ; 
 int VTU_PURGE ; 
 int /*<<< orphan*/  VTU_VID ; 
 int VTU_VID_MASK ; 
 int VTU_VID_VALID ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  e6000sw_writereg (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
e6000sw_vtu_update(e6000sw_softc_t *sc, int purge, int vid, int fid,
    int members, int untagged)
{
	int i, op;
	uint32_t data[2];

	if (E6000SW_WAITREADY(sc, VTU_OPERATION, VTU_BUSY)) {
		device_printf(sc->dev, "VTU unit is busy, cannot access\n");
		return (EBUSY);
	}

	*data = (vid & VTU_VID_MASK);
	if (purge == 0)
		*data |= VTU_VID_VALID;
	e6000sw_writereg(sc, REG_GLOBAL, VTU_VID, *data);

	if (purge == 0) {
		data[0] = 0;
		data[1] = 0;
		for (i = 0; i < sc->num_ports; i++) {
			if ((untagged & (1 << i)) != 0)
				data[i / VTU_PPREG(sc)] |=
				    VTU_PORT_UNTAGGED << VTU_PORT(sc, i);
			else if ((members & (1 << i)) != 0)
				data[i / VTU_PPREG(sc)] |=
				    VTU_PORT_TAGGED << VTU_PORT(sc, i);
			else
				data[i / VTU_PPREG(sc)] |=
				    VTU_PORT_DISCARD << VTU_PORT(sc, i);
		}
		e6000sw_writereg(sc, REG_GLOBAL, VTU_DATA, data[0]);
		e6000sw_writereg(sc, REG_GLOBAL, VTU_DATA2, data[1]);
		e6000sw_writereg(sc, REG_GLOBAL, VTU_FID,
		    fid & VTU_FID_MASK(sc));
		op = VTU_LOAD;
	} else
		op = VTU_PURGE;

	e6000sw_writereg(sc, REG_GLOBAL, VTU_OPERATION, op | VTU_BUSY);
	if (E6000SW_WAITREADY(sc, VTU_OPERATION, VTU_BUSY)) {
		device_printf(sc->dev, "Timeout while flushing VTU\n");
		return (ETIMEDOUT);
	}

	return (0);
}