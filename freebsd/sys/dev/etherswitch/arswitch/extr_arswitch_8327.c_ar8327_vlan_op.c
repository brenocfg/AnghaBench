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
typedef  int uint32_t ;
struct arswitch_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR8327_REG_VTU_FUNC0 ; 
 int /*<<< orphan*/  AR8327_REG_VTU_FUNC1 ; 
 int AR8327_VTU_FUNC1_BUSY ; 
 int AR8327_VTU_FUNC1_OP ; 
 int AR8327_VTU_FUNC1_OP_LOAD ; 
 int AR8327_VTU_FUNC1_VID_S ; 
 int EBUSY ; 
 scalar_t__ arswitch_waitreg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int arswitch_writereg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ar8327_vlan_op(struct arswitch_softc *sc, uint32_t op, uint32_t vid,
    uint32_t data)
{
	int err;

	/*
	 * Wait for the "done" bit to finish.
	 */
	if (arswitch_waitreg(sc->sc_dev, AR8327_REG_VTU_FUNC1,
	    AR8327_VTU_FUNC1_BUSY, 0, 5))
		return (EBUSY);

	/*
	 * If it's a "load" operation, then ensure 'data' is loaded
	 * in first.
	 */
	if ((op & AR8327_VTU_FUNC1_OP) == AR8327_VTU_FUNC1_OP_LOAD) {
		err = arswitch_writereg(sc->sc_dev, AR8327_REG_VTU_FUNC0, data);
		if (err)
			return (err);
	}

	/*
	 * Set the VID.
	 */
	op |= ((vid & 0xfff) << AR8327_VTU_FUNC1_VID_S);

	/*
	 * Set busy bit to start loading in the command.
	 */
	op |= AR8327_VTU_FUNC1_BUSY;
	arswitch_writereg(sc->sc_dev, AR8327_REG_VTU_FUNC1, op);

	/*
	 * Finally - wait for it to load.
	 */
	if (arswitch_waitreg(sc->sc_dev, AR8327_REG_VTU_FUNC1,
	    AR8327_VTU_FUNC1_BUSY, 0, 5))
		return (EBUSY);

	return (0);
}