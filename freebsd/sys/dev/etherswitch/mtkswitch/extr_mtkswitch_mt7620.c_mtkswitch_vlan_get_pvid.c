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
struct TYPE_2__ {int (* mtkswitch_read ) (struct mtkswitch_softc*,int /*<<< orphan*/ ) ;} ;
struct mtkswitch_softc {TYPE_1__ hal; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MTKSWITCH_LOCK_ASSERT (struct mtkswitch_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTKSWITCH_PPBV1 (int) ; 
 int PPBV_VID_FROM_REG (int) ; 
 int stub1 (struct mtkswitch_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mtkswitch_vlan_get_pvid(struct mtkswitch_softc *sc, int port, int *pvid)
{

	MTKSWITCH_LOCK_ASSERT(sc, MA_OWNED);

	*pvid = sc->hal.mtkswitch_read(sc, MTKSWITCH_PPBV1(port));
	*pvid = PPBV_VID_FROM_REG(*pvid);

	return (0); 
}