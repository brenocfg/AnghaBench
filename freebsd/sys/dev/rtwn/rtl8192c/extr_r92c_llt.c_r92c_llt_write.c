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
typedef  int /*<<< orphan*/  uint32_t ;
struct rtwn_softc {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 scalar_t__ MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R92C_LLT_INIT ; 
 int /*<<< orphan*/  R92C_LLT_INIT_ADDR ; 
 int /*<<< orphan*/  R92C_LLT_INIT_DATA ; 
 int /*<<< orphan*/  R92C_LLT_INIT_OP ; 
 scalar_t__ R92C_LLT_INIT_OP_NO_ACTIVE ; 
 int /*<<< orphan*/  R92C_LLT_INIT_OP_WRITE ; 
 int SM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtwn_delay (struct rtwn_softc*,int) ; 
 int /*<<< orphan*/  rtwn_read_4 (struct rtwn_softc*,int /*<<< orphan*/ ) ; 
 int rtwn_write_4 (struct rtwn_softc*,int /*<<< orphan*/ ,int) ; 

int
r92c_llt_write(struct rtwn_softc *sc, uint32_t addr, uint32_t data)
{
	int ntries, error;

	error = rtwn_write_4(sc, R92C_LLT_INIT,
	    SM(R92C_LLT_INIT_OP, R92C_LLT_INIT_OP_WRITE) |
	    SM(R92C_LLT_INIT_ADDR, addr) |
	    SM(R92C_LLT_INIT_DATA, data));
	if (error != 0)
		return (error);
	/* Wait for write operation to complete. */
	for (ntries = 0; ntries < 20; ntries++) {
		if (MS(rtwn_read_4(sc, R92C_LLT_INIT), R92C_LLT_INIT_OP) ==
		    R92C_LLT_INIT_OP_NO_ACTIVE)
			return (0);
		rtwn_delay(sc, 10);
	}
	return (ETIMEDOUT);
}