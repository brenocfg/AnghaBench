#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct seeprom_config {int max_targets; int brtime_id; int* device_flags; int bios_control; int adapter_control; } ;
struct ahd_transinfo {int protocol_version; int transport_version; int ppr_options; int period; int offset; int width; } ;
struct ahd_tmode_tstate {int discenable; int tagenable; } ;
struct ahd_softc {int our_id; int user_discenable; int user_tagenable; int features; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int protocol_version; int transport_version; } ;
struct TYPE_3__ {int protocol_version; int transport_version; } ;
struct ahd_initiator_tinfo {TYPE_2__ curr; TYPE_1__ goal; struct ahd_transinfo user; } ;
struct ahd_devinfo {int dummy; } ;

/* Variables and functions */
 int AHD_ASYNC_XFER_PERIOD ; 
 int /*<<< orphan*/  AHD_BIOS_ENABLED ; 
 int /*<<< orphan*/  AHD_EXTENDED_TRANS_A ; 
 int /*<<< orphan*/  AHD_FATAL_ERROR (struct ahd_softc*) ; 
 int AHD_PERIOD_10MHz ; 
 int /*<<< orphan*/  AHD_RESET_BUS_A ; 
 int AHD_RTI ; 
 int AHD_SHOW_MISC ; 
 int /*<<< orphan*/  AHD_SPCHK_ENB_A ; 
 int /*<<< orphan*/  AHD_STPWLEVEL_A ; 
 int AHD_SYNCRATE_160 ; 
 int AHD_SYNCRATE_DT ; 
 int AHD_TRANS_CUR ; 
 int AHD_TRANS_GOAL ; 
 int /*<<< orphan*/  CAM_LUN_WILDCARD ; 
 int CFBIOSSTATE ; 
 int CFBS_ENABLED ; 
 int CFDISC ; 
 int CFEXTEND ; 
 int CFMAXTARG ; 
 int CFPACKETIZED ; 
 int CFQAS ; 
 int CFRESETB ; 
 int CFSCSIID ; 
 int CFSPARITY ; 
 int CFSTPWLEVEL ; 
 int CFWIDEB ; 
 int CFXFER ; 
 int CFXFER_ASYNC ; 
 int ENOMEM ; 
 int MAX_OFFSET ; 
 int MSG_EXT_PPR_DT_REQ ; 
 int MSG_EXT_PPR_HOLD_MCS ; 
 int MSG_EXT_PPR_IU_REQ ; 
 int MSG_EXT_PPR_QAS_REQ ; 
 int MSG_EXT_PPR_RD_STRM ; 
 int MSG_EXT_PPR_RTI ; 
 int MSG_EXT_PPR_WR_FLOW ; 
 int MSG_EXT_WDTR_BUS_16_BIT ; 
 int MSG_EXT_WDTR_BUS_8_BIT ; 
 int /*<<< orphan*/  ROLE_INITIATOR ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * ahd_alloc_tstate (struct ahd_softc*,int,char) ; 
 int /*<<< orphan*/  ahd_compile_devinfo (struct ahd_devinfo*,int,int,int /*<<< orphan*/ ,char,int /*<<< orphan*/ ) ; 
 int ahd_debug ; 
 struct ahd_initiator_tinfo* ahd_fetch_transinfo (struct ahd_softc*,char,int,int,struct ahd_tmode_tstate**) ; 
 char* ahd_name (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_set_syncrate (struct ahd_softc*,struct ahd_devinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_set_width (struct ahd_softc*,struct ahd_devinfo*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int
ahd_parse_cfgdata(struct ahd_softc *ahd, struct seeprom_config *sc)
{
	int targ;
	int max_targ;

	max_targ = sc->max_targets & CFMAXTARG;
	ahd->our_id = sc->brtime_id & CFSCSIID;

	/*
	 * Allocate a tstate to house information for our
	 * initiator presence on the bus as well as the user
	 * data for any target mode initiator.
	 */
	if (ahd_alloc_tstate(ahd, ahd->our_id, 'A') == NULL) {
		printf("%s: unable to allocate ahd_tmode_tstate.  "
		       "Failing attach\n", ahd_name(ahd));
		AHD_FATAL_ERROR(ahd);
		return (ENOMEM);
	}

	for (targ = 0; targ < max_targ; targ++) {
		struct	 ahd_devinfo devinfo;
		struct	 ahd_initiator_tinfo *tinfo;
		struct	 ahd_transinfo *user_tinfo;
		struct	 ahd_tmode_tstate *tstate;
		uint16_t target_mask;

		tinfo = ahd_fetch_transinfo(ahd, 'A', ahd->our_id,
					    targ, &tstate);
		user_tinfo = &tinfo->user;

		/*
		 * We support SPC2 and SPI4.
		 */
		tinfo->user.protocol_version = 4;
		tinfo->user.transport_version = 4;

		target_mask = 0x01 << targ;
		ahd->user_discenable &= ~target_mask;
		tstate->discenable &= ~target_mask;
		ahd->user_tagenable &= ~target_mask;
		if (sc->device_flags[targ] & CFDISC) {
			tstate->discenable |= target_mask;
			ahd->user_discenable |= target_mask;
			ahd->user_tagenable |= target_mask;
		} else {
			/*
			 * Cannot be packetized without disconnection.
			 */
			sc->device_flags[targ] &= ~CFPACKETIZED;
		}

		user_tinfo->ppr_options = 0;
		user_tinfo->period = (sc->device_flags[targ] & CFXFER);
		if (user_tinfo->period < CFXFER_ASYNC) {
			if (user_tinfo->period <= AHD_PERIOD_10MHz)
				user_tinfo->ppr_options |= MSG_EXT_PPR_DT_REQ;
			user_tinfo->offset = MAX_OFFSET;
		} else  {
			user_tinfo->offset = 0;
			user_tinfo->period = AHD_ASYNC_XFER_PERIOD;
		}
#ifdef AHD_FORCE_160
		if (user_tinfo->period <= AHD_SYNCRATE_160)
			user_tinfo->period = AHD_SYNCRATE_DT;
#endif

		if ((sc->device_flags[targ] & CFPACKETIZED) != 0) {
			user_tinfo->ppr_options |= MSG_EXT_PPR_RD_STRM
						|  MSG_EXT_PPR_WR_FLOW
						|  MSG_EXT_PPR_HOLD_MCS
						|  MSG_EXT_PPR_IU_REQ;
			if ((ahd->features & AHD_RTI) != 0)
				user_tinfo->ppr_options |= MSG_EXT_PPR_RTI;
		}

		if ((sc->device_flags[targ] & CFQAS) != 0)
			user_tinfo->ppr_options |= MSG_EXT_PPR_QAS_REQ;

		if ((sc->device_flags[targ] & CFWIDEB) != 0)
			user_tinfo->width = MSG_EXT_WDTR_BUS_16_BIT;
		else
			user_tinfo->width = MSG_EXT_WDTR_BUS_8_BIT;
#ifdef AHD_DEBUG
		if ((ahd_debug & AHD_SHOW_MISC) != 0)
			printf("(%d): %x:%x:%x:%x\n", targ, user_tinfo->width,
			       user_tinfo->period, user_tinfo->offset,
			       user_tinfo->ppr_options);
#endif
		/*
		 * Start out Async/Narrow/Untagged and with
		 * conservative protocol support.
		 */
		tstate->tagenable &= ~target_mask;
		tinfo->goal.protocol_version = 2;
		tinfo->goal.transport_version = 2;
		tinfo->curr.protocol_version = 2;
		tinfo->curr.transport_version = 2;
		ahd_compile_devinfo(&devinfo, ahd->our_id,
				    targ, CAM_LUN_WILDCARD,
				    'A', ROLE_INITIATOR);
		ahd_set_width(ahd, &devinfo, MSG_EXT_WDTR_BUS_8_BIT,
			      AHD_TRANS_CUR|AHD_TRANS_GOAL, /*paused*/TRUE);
		ahd_set_syncrate(ahd, &devinfo, /*period*/0, /*offset*/0,
				 /*ppr_options*/0, AHD_TRANS_CUR|AHD_TRANS_GOAL,
				 /*paused*/TRUE);
	}

	ahd->flags &= ~AHD_SPCHK_ENB_A;
	if (sc->bios_control & CFSPARITY)
		ahd->flags |= AHD_SPCHK_ENB_A;

	ahd->flags &= ~AHD_RESET_BUS_A;
	if (sc->bios_control & CFRESETB)
		ahd->flags |= AHD_RESET_BUS_A;

	ahd->flags &= ~AHD_EXTENDED_TRANS_A;
	if (sc->bios_control & CFEXTEND)
		ahd->flags |= AHD_EXTENDED_TRANS_A;

	ahd->flags &= ~AHD_BIOS_ENABLED;
	if ((sc->bios_control & CFBIOSSTATE) == CFBS_ENABLED)
		ahd->flags |= AHD_BIOS_ENABLED;

	ahd->flags &= ~AHD_STPWLEVEL_A;
	if ((sc->adapter_control & CFSTPWLEVEL) != 0)
		ahd->flags |= AHD_STPWLEVEL_A;

	return (0);
}