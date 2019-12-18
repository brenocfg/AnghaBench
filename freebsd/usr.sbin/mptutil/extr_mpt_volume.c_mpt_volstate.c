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
typedef  int U8 ;

/* Variables and functions */
#define  MPI_RAIDVOL0_STATUS_STATE_DEGRADED 131 
#define  MPI_RAIDVOL0_STATUS_STATE_FAILED 130 
#define  MPI_RAIDVOL0_STATUS_STATE_MISSING 129 
#define  MPI_RAIDVOL0_STATUS_STATE_OPTIMAL 128 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

const char *
mpt_volstate(U8 State)
{
	static char buf[16];

	switch (State) {
	case MPI_RAIDVOL0_STATUS_STATE_OPTIMAL:
		return ("OPTIMAL");
	case MPI_RAIDVOL0_STATUS_STATE_DEGRADED:
		return ("DEGRADED");
	case MPI_RAIDVOL0_STATUS_STATE_FAILED:
		return ("FAILED");
	case MPI_RAIDVOL0_STATUS_STATE_MISSING:
		return ("MISSING");
	default:
		sprintf(buf, "VSTATE 0x%02x", State);
		return (buf);
	}
}