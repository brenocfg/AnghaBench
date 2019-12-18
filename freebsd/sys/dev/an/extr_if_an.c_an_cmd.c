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
struct an_softc {int /*<<< orphan*/  mpi350; } ;

/* Variables and functions */
 int AN_CMD_BUSY ; 
 int /*<<< orphan*/  AN_COMMAND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AN_EVENT_ACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AN_EVENT_STAT (int /*<<< orphan*/ ) ; 
 int AN_EV_CLR_STUCK_BUSY ; 
 int AN_EV_CMD ; 
 int /*<<< orphan*/  AN_LOCK_ASSERT (struct an_softc*) ; 
 int /*<<< orphan*/  AN_PARAM0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AN_PARAM1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AN_PARAM2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AN_RESP0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AN_RESP1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AN_RESP2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AN_STATUS (int /*<<< orphan*/ ) ; 
 int AN_STAT_CMD_CODE ; 
 int AN_TIMEOUT ; 
 int CSR_READ_2 (struct an_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct an_softc*,int /*<<< orphan*/ ,int) ; 
 int ETIMEDOUT ; 

__attribute__((used)) static int
an_cmd(struct an_softc *sc, int cmd, int val)
{
	int			i, s = 0;

	AN_LOCK_ASSERT(sc);
	CSR_WRITE_2(sc, AN_PARAM0(sc->mpi350), val);
	CSR_WRITE_2(sc, AN_PARAM1(sc->mpi350), 0);
	CSR_WRITE_2(sc, AN_PARAM2(sc->mpi350), 0);
	CSR_WRITE_2(sc, AN_COMMAND(sc->mpi350), cmd);

	for (i = 0; i < AN_TIMEOUT; i++) {
		if (CSR_READ_2(sc, AN_EVENT_STAT(sc->mpi350)) & AN_EV_CMD)
			break;
		else {
			if (CSR_READ_2(sc, AN_COMMAND(sc->mpi350)) == cmd)
				CSR_WRITE_2(sc, AN_COMMAND(sc->mpi350), cmd);
		}
	}

	for (i = 0; i < AN_TIMEOUT; i++) {
		CSR_READ_2(sc, AN_RESP0(sc->mpi350));
		CSR_READ_2(sc, AN_RESP1(sc->mpi350));
		CSR_READ_2(sc, AN_RESP2(sc->mpi350));
		s = CSR_READ_2(sc, AN_STATUS(sc->mpi350));
		if ((s & AN_STAT_CMD_CODE) == (cmd & AN_STAT_CMD_CODE))
			break;
	}

	/* Ack the command */
	CSR_WRITE_2(sc, AN_EVENT_ACK(sc->mpi350), AN_EV_CMD);

	if (CSR_READ_2(sc, AN_COMMAND(sc->mpi350)) & AN_CMD_BUSY)
		CSR_WRITE_2(sc, AN_EVENT_ACK(sc->mpi350), AN_EV_CLR_STUCK_BUSY);

	if (i == AN_TIMEOUT)
		return(ETIMEDOUT);

	return(0);
}