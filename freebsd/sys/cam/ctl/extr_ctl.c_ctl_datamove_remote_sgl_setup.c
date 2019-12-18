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
struct TYPE_2__ {scalar_t__ kern_data_len; int kern_sg_entries; } ;
union ctl_io {TYPE_1__ scsiio; } ;
typedef  scalar_t__ uint32_t ;
struct ctl_sg_entry {scalar_t__ len; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_HA_DATAMOVE_SEGMENT ; 
 struct ctl_sg_entry* CTL_LSGL (union ctl_io*) ; 
 scalar_t__ MIN (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_CTL ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  malloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ctl_datamove_remote_sgl_setup(union ctl_io *io)
{
	struct ctl_sg_entry *local_sglist;
	uint32_t len_to_go;
	int retval;
	int i;

	retval = 0;
	local_sglist = CTL_LSGL(io);
	len_to_go = io->scsiio.kern_data_len;

	/*
	 * The difficult thing here is that the size of the various
	 * S/G segments may be different than the size from the
	 * remote controller.  That'll make it harder when DMAing
	 * the data back to the other side.
	 */
	for (i = 0; len_to_go > 0; i++) {
		local_sglist[i].len = MIN(len_to_go, CTL_HA_DATAMOVE_SEGMENT);
		local_sglist[i].addr =
		    malloc(local_sglist[i].len, M_CTL, M_WAITOK);

		len_to_go -= local_sglist[i].len;
	}
	/*
	 * Reset the number of S/G entries accordingly.  The original
	 * number of S/G entries is available in rem_sg_entries.
	 */
	io->scsiio.kern_sg_entries = i;

	return (retval);
}