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
struct mps_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ETIMEDOUT ; 
 int MPI2_HIS_IOC2SYS_DB_STATUS ; 
 int /*<<< orphan*/  MPI2_HOST_INTERRUPT_STATUS_OFFSET ; 
 int MPS_DB_MAX_WAIT ; 
 int mps_regread (struct mps_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mps_wait_db_int(struct mps_softc *sc)
{
	int retry;

	for (retry = 0; retry < MPS_DB_MAX_WAIT; retry++) {
		if ((mps_regread(sc, MPI2_HOST_INTERRUPT_STATUS_OFFSET) &
		    MPI2_HIS_IOC2SYS_DB_STATUS) != 0)
			return (0);
		DELAY(2000);
	}
	return (ETIMEDOUT);
}