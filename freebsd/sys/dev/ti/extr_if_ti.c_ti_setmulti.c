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
struct ti_softc {struct ifnet* ti_ifp; } ;
struct ti_cmd_desc {int dummy; } ;
struct ifnet {int if_flags; } ;

/* Variables and functions */
 int CSR_READ_4 (struct ti_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct ti_softc*,int /*<<< orphan*/ ,int) ; 
 int IFF_ALLMULTI ; 
 int /*<<< orphan*/  TI_CMD_CODE_ALLMULTI_DIS ; 
 int /*<<< orphan*/  TI_CMD_CODE_ALLMULTI_ENB ; 
 int /*<<< orphan*/  TI_CMD_SET_ALLMULTI ; 
 int /*<<< orphan*/  TI_DO_CMD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TI_LOCK_ASSERT (struct ti_softc*) ; 
 int /*<<< orphan*/  TI_MB_HOSTINTR ; 
 int /*<<< orphan*/  if_foreach_llmaddr (struct ifnet*,int /*<<< orphan*/ ,struct ti_softc*) ; 
 int /*<<< orphan*/  ti_add_mcast ; 
 int /*<<< orphan*/  ti_del_mcast ; 

__attribute__((used)) static void
ti_setmulti(struct ti_softc *sc)
{
	struct ifnet *ifp;
	struct ti_cmd_desc cmd;
	uint32_t intrs;

	TI_LOCK_ASSERT(sc);

	ifp = sc->ti_ifp;

	if (ifp->if_flags & IFF_ALLMULTI) {
		TI_DO_CMD(TI_CMD_SET_ALLMULTI, TI_CMD_CODE_ALLMULTI_ENB, 0);
		return;
	} else {
		TI_DO_CMD(TI_CMD_SET_ALLMULTI, TI_CMD_CODE_ALLMULTI_DIS, 0);
	}

	/* Disable interrupts. */
	intrs = CSR_READ_4(sc, TI_MB_HOSTINTR);
	CSR_WRITE_4(sc, TI_MB_HOSTINTR, 1);

	/* First, zot all the existing filters. */
	if_foreach_llmaddr(ifp, ti_del_mcast, sc);

	/* Now program new ones. */
	if_foreach_llmaddr(ifp, ti_add_mcast, sc);

	/* Re-enable interrupts. */
	CSR_WRITE_4(sc, TI_MB_HOSTINTR, intrs);
}