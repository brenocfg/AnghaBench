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
struct mtkswitch_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MTKSWITCH_LOCK_ASSERT (struct mtkswitch_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTKSWITCH_PVID (int) ; 
 int MTKSWITCH_READ (struct mtkswitch_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTKSWITCH_WRITE (struct mtkswitch_softc*,int /*<<< orphan*/ ,int) ; 
 int PVID_MASK ; 
 int PVID_OFF (int) ; 

__attribute__((used)) static int
mtkswitch_vlan_set_pvid(struct mtkswitch_softc *sc, int port, int pvid)
{
	uint32_t val;

	MTKSWITCH_LOCK_ASSERT(sc, MA_OWNED);
	val = MTKSWITCH_READ(sc, MTKSWITCH_PVID(port));
	val &= ~(PVID_MASK << PVID_OFF(port));
	val |= (pvid & PVID_MASK) << PVID_OFF(port);
	MTKSWITCH_WRITE(sc, MTKSWITCH_PVID(port), val);
	
	return (0);
}