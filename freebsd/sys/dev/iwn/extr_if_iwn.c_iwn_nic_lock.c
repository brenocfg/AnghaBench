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
struct iwn_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  IWN_GP_CNTRL ; 
 int IWN_GP_CNTRL_MAC_ACCESS_ENA ; 
 int /*<<< orphan*/  IWN_GP_CNTRL_MAC_ACCESS_REQ ; 
 int IWN_GP_CNTRL_SLEEP ; 
 int IWN_READ (struct iwn_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWN_SETBITS (struct iwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iwn_nic_lock(struct iwn_softc *sc)
{
	int ntries;

	/* Request exclusive access to NIC. */
	IWN_SETBITS(sc, IWN_GP_CNTRL, IWN_GP_CNTRL_MAC_ACCESS_REQ);

	/* Spin until we actually get the lock. */
	for (ntries = 0; ntries < 1000; ntries++) {
		if ((IWN_READ(sc, IWN_GP_CNTRL) &
		     (IWN_GP_CNTRL_MAC_ACCESS_ENA | IWN_GP_CNTRL_SLEEP)) ==
		    IWN_GP_CNTRL_MAC_ACCESS_ENA)
			return 0;
		DELAY(10);
	}
	return ETIMEDOUT;
}