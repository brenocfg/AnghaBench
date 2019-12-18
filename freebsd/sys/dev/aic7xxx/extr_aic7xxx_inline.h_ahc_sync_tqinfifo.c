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
struct target_cmd {int dummy; } ;
struct ahc_softc {int flags; int /*<<< orphan*/  shared_data_dmamap; int /*<<< orphan*/  shared_data_dmat; } ;

/* Variables and functions */
 int AHC_TARGETROLE ; 
 int AHC_TMODE_CMDS ; 
 int /*<<< orphan*/  ahc_targetcmd_offset (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aic_dmamap_sync (struct ahc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static __inline void
ahc_sync_tqinfifo(struct ahc_softc *ahc, int op)
{
#ifdef AHC_TARGET_MODE
	if ((ahc->flags & AHC_TARGETROLE) != 0) {
		aic_dmamap_sync(ahc, ahc->shared_data_dmat,
				ahc->shared_data_dmamap,
				ahc_targetcmd_offset(ahc, 0),
				sizeof(struct target_cmd) * AHC_TMODE_CMDS,
				op);
	}
#endif
}