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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* mtkswitch_write ) (struct mtkswitch_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct mtkswitch_softc {TYPE_1__ hal; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MTKSWITCH_LOCK_ASSERT (struct mtkswitch_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTKSWITCH_PPBV1 (int) ; 
 int /*<<< orphan*/  MTKSWITCH_PPBV2 (int) ; 
 int /*<<< orphan*/  PPBV_VID (int) ; 
 int PPBV_VID_MASK ; 
 int /*<<< orphan*/  stub1 (struct mtkswitch_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct mtkswitch_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mtkswitch_vlan_set_pvid(struct mtkswitch_softc *sc, int port, int pvid)
{
	uint32_t val;

	MTKSWITCH_LOCK_ASSERT(sc, MA_OWNED);
	val = PPBV_VID(pvid & PPBV_VID_MASK);
	sc->hal.mtkswitch_write(sc, MTKSWITCH_PPBV1(port), val);
	sc->hal.mtkswitch_write(sc, MTKSWITCH_PPBV2(port), val);

	return (0);
}