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
struct target_cmd {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dmamap; } ;
struct ahd_softc {int flags; TYPE_1__ shared_data_map; int /*<<< orphan*/  shared_data_dmat; } ;

/* Variables and functions */
 int AHD_TARGETROLE ; 
 int AHD_TMODE_CMDS ; 
 int /*<<< orphan*/  ahd_targetcmd_offset (struct ahd_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aic_dmamap_sync (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static __inline void
ahd_sync_tqinfifo(struct ahd_softc *ahd, int op)
{
#ifdef AHD_TARGET_MODE
	if ((ahd->flags & AHD_TARGETROLE) != 0) {
		aic_dmamap_sync(ahd, ahd->shared_data_dmat,
				ahd->shared_data_map.dmamap,
				ahd_targetcmd_offset(ahd, 0),
				sizeof(struct target_cmd) * AHD_TMODE_CMDS,
				op);
	}
#endif
}