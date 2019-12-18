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
struct mtkswitch_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MTKSWITCH_LOCK_ASSERT (struct mtkswitch_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTKSWITCH_PVID (int) ; 
 int MTKSWITCH_READ (struct mtkswitch_softc*,int /*<<< orphan*/ ) ; 
 int PVID_MASK ; 
 int PVID_OFF (int) ; 

__attribute__((used)) static int
mtkswitch_vlan_get_pvid(struct mtkswitch_softc *sc, int port, int *pvid)
{

	MTKSWITCH_LOCK_ASSERT(sc, MA_OWNED);
	*pvid = (MTKSWITCH_READ(sc, MTKSWITCH_PVID(port)) >> PVID_OFF(port)) &
	    PVID_MASK;

	return (0); 
}