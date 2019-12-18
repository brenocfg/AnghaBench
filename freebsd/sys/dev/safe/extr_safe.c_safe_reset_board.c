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
typedef  int u_int32_t ;
struct safe_softc {int dummy; } ;

/* Variables and functions */
 int READ_REG (struct safe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAFE_PE_DMACFG ; 
 int SAFE_PE_DMACFG_PDRRESET ; 
 int SAFE_PE_DMACFG_PERESET ; 
 int SAFE_PE_DMACFG_SGRESET ; 
 int /*<<< orphan*/  WRITE_REG (struct safe_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
safe_reset_board(struct safe_softc *sc)
{
	u_int32_t v;
	/*
	 * Reset the device.  The manual says no delay
	 * is needed between marking and clearing reset.
	 */
	v = READ_REG(sc, SAFE_PE_DMACFG) &~
		(SAFE_PE_DMACFG_PERESET | SAFE_PE_DMACFG_PDRRESET |
		 SAFE_PE_DMACFG_SGRESET);
	WRITE_REG(sc, SAFE_PE_DMACFG, v
				    | SAFE_PE_DMACFG_PERESET
				    | SAFE_PE_DMACFG_PDRRESET
				    | SAFE_PE_DMACFG_SGRESET);
	WRITE_REG(sc, SAFE_PE_DMACFG, v);
}