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
typedef  int /*<<< orphan*/  u_int ;
struct target_cmd {int dummy; } ;
struct ahc_softc {size_t qoutfifonext; scalar_t__* qoutfifo; int flags; size_t tqinfifonext; TYPE_1__* targetcmds; int /*<<< orphan*/  tqinfifofnext; int /*<<< orphan*/  shared_data_dmamap; int /*<<< orphan*/  shared_data_dmat; } ;
struct TYPE_2__ {scalar_t__ cmd_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHC_RUN_QOUTFIFO ; 
 int /*<<< orphan*/  AHC_RUN_TQINFIFO ; 
 int AHC_TARGETROLE ; 
 int AHC_TQINFIFO_BLOCKED ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 scalar_t__ SCB_LIST_NULL ; 
 size_t ahc_targetcmd_offset (struct ahc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aic_dmamap_sync (struct ahc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline u_int
ahc_check_cmdcmpltqueues(struct ahc_softc *ahc)
{
	u_int retval;

	retval = 0;
	aic_dmamap_sync(ahc, ahc->shared_data_dmat, ahc->shared_data_dmamap,
			/*offset*/ahc->qoutfifonext, /*len*/1,
			BUS_DMASYNC_POSTREAD);
	if (ahc->qoutfifo[ahc->qoutfifonext] != SCB_LIST_NULL)
		retval |= AHC_RUN_QOUTFIFO;
#ifdef AHC_TARGET_MODE
	if ((ahc->flags & AHC_TARGETROLE) != 0
	 && (ahc->flags & AHC_TQINFIFO_BLOCKED) == 0) {
		aic_dmamap_sync(ahc, ahc->shared_data_dmat,
				ahc->shared_data_dmamap,
				ahc_targetcmd_offset(ahc, ahc->tqinfifofnext),
				/*len*/sizeof(struct target_cmd),
				BUS_DMASYNC_POSTREAD);
		if (ahc->targetcmds[ahc->tqinfifonext].cmd_valid != 0)
			retval |= AHC_RUN_TQINFIFO;
	}
#endif
	return (retval);
}