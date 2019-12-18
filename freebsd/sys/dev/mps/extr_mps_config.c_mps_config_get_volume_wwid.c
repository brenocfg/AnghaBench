#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct mps_softc {int dummy; } ;
struct TYPE_4__ {int Low; scalar_t__ High; } ;
struct TYPE_5__ {TYPE_1__ WWID; } ;
typedef  TYPE_2__ Mpi2RaidVolPage1_t ;
typedef  int /*<<< orphan*/  Mpi2ConfigReply_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPI2_RAID_VOLUME_PGAD_FORM_HANDLE ; 
 int le64toh (int) ; 
 int /*<<< orphan*/  mps_config_get_raid_volume_pg1 (struct mps_softc*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
mps_config_get_volume_wwid(struct mps_softc *sc, u16 volume_handle, u64 *wwid)
{
	Mpi2ConfigReply_t mpi_reply;
	Mpi2RaidVolPage1_t raid_vol_pg1;

	*wwid = 0;
	if (!(mps_config_get_raid_volume_pg1(sc, &mpi_reply, &raid_vol_pg1,
	    MPI2_RAID_VOLUME_PGAD_FORM_HANDLE, volume_handle))) {
		*wwid = le64toh((u64)raid_vol_pg1.WWID.High << 32 |
		    raid_vol_pg1.WWID.Low);
		return 0;
	} else
		return -1;
}