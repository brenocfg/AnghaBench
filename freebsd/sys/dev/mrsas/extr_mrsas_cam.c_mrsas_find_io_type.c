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
struct TYPE_2__ {int* cdb_bytes; } ;
struct ccb_scsiio {TYPE_1__ cdb_io; } ;
union ccb {struct ccb_scsiio csio; } ;
struct cam_sim {int dummy; } ;

/* Variables and functions */
 int NON_READ_WRITE_LDIO ; 
 int NON_READ_WRITE_SYSPDIO ; 
#define  READ_10 135 
#define  READ_12 134 
#define  READ_16 133 
#define  READ_6 132 
 int READ_WRITE_LDIO ; 
 int READ_WRITE_SYSPDIO ; 
#define  WRITE_10 131 
#define  WRITE_12 130 
#define  WRITE_16 129 
#define  WRITE_6 128 
 int /*<<< orphan*/  cam_sim_bus (struct cam_sim*) ; 

int 
mrsas_find_io_type(struct cam_sim *sim, union ccb *ccb)
{
	struct ccb_scsiio *csio = &(ccb->csio);

	switch (csio->cdb_io.cdb_bytes[0]) {
	case READ_10:
	case WRITE_10:
	case READ_12:
	case WRITE_12:
	case READ_6:
	case WRITE_6:
	case READ_16:
	case WRITE_16:
		return (cam_sim_bus(sim) ?
		    READ_WRITE_SYSPDIO : READ_WRITE_LDIO);
	default:
		return (cam_sim_bus(sim) ?
		    NON_READ_WRITE_SYSPDIO : NON_READ_WRITE_LDIO);
	}
}