#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  union ctl_io {int dummy; } ctl_io ;
struct TYPE_8__ {int residx; int res_type; int /*<<< orphan*/  sa_res_key; void* action; } ;
struct TYPE_7__ {TYPE_4__ pr_info; } ;
struct TYPE_6__ {void* msg_type; int /*<<< orphan*/  nexus; } ;
union ctl_ha_msg {TYPE_3__ pr; TYPE_2__ hdr; } ;
typedef  int uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct scsi_per_res_out_parms {int /*<<< orphan*/  serv_act_res_key; } ;
struct scsi_per_res_out {int scope_type; } ;
struct ctl_softc {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  nexus; } ;
struct ctl_scsiio {TYPE_1__ io_hdr; int /*<<< orphan*/  kern_data_ptr; } ;
struct ctl_lun {int pr_res_idx; int pr_key_count; int pr_res_type; int flags; int /*<<< orphan*/  lun_lock; int /*<<< orphan*/  pr_generation; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_HA_CHAN_CTL ; 
 int CTL_LUN_PR_RESERVED ; 
 int CTL_MAX_INITIATORS ; 
 void* CTL_MSG_PERS_ACTION ; 
 int CTL_PR_ALL_REGISTRANTS ; 
 void* CTL_PR_PREEMPT ; 
 int CTL_RETVAL_COMPLETE ; 
 int /*<<< orphan*/  CTL_UA_REG_PREEMPT ; 
 int /*<<< orphan*/  CTL_UA_RES_RELEASE ; 
 int /*<<< orphan*/  M_CTL ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int SPR_LU_SCOPE ; 
 int SPR_SCOPE_MASK ; 
 int SPR_TYPE_EX_AC_AR ; 
 int SPR_TYPE_EX_AC_RO ; 
 int SPR_TYPE_WR_EX_AR ; 
 int SPR_TYPE_WR_EX_RO ; 
 int /*<<< orphan*/  ctl_clr_prkey (struct ctl_lun*,int) ; 
 int /*<<< orphan*/  ctl_done (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_est_ua (struct ctl_lun*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ctl_get_prkey (struct ctl_lun*,int) ; 
 int /*<<< orphan*/  ctl_ha_msg_send (int /*<<< orphan*/ ,union ctl_ha_msg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_set_invalid_field (struct ctl_scsiio*,int,int,int,int,int) ; 
 int /*<<< orphan*/  ctl_set_reservation_conflict (struct ctl_scsiio*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ctl_pro_preempt(struct ctl_softc *softc, struct ctl_lun *lun, uint64_t res_key,
		uint64_t sa_res_key, uint8_t type, uint32_t residx,
		struct ctl_scsiio *ctsio, struct scsi_per_res_out *cdb,
		struct scsi_per_res_out_parms* param)
{
	union ctl_ha_msg persis_io;
	int i;

	mtx_lock(&lun->lun_lock);
	if (sa_res_key == 0) {
		if (lun->pr_res_idx == CTL_PR_ALL_REGISTRANTS) {
			/* validate scope and type */
			if ((cdb->scope_type & SPR_SCOPE_MASK) !=
			     SPR_LU_SCOPE) {
				mtx_unlock(&lun->lun_lock);
				ctl_set_invalid_field(/*ctsio*/ ctsio,
						      /*sks_valid*/ 1,
						      /*command*/ 1,
						      /*field*/ 2,
						      /*bit_valid*/ 1,
						      /*bit*/ 4);
				ctl_done((union ctl_io *)ctsio);
				return (1);
			}

		        if (type>8 || type==2 || type==4 || type==0) {
				mtx_unlock(&lun->lun_lock);
				ctl_set_invalid_field(/*ctsio*/ ctsio,
       	           				      /*sks_valid*/ 1,
						      /*command*/ 1,
						      /*field*/ 2,
						      /*bit_valid*/ 1,
						      /*bit*/ 0);
				ctl_done((union ctl_io *)ctsio);
				return (1);
		        }

			/*
			 * Unregister everybody else and build UA for
			 * them
			 */
			for(i = 0; i < CTL_MAX_INITIATORS; i++) {
				if (i == residx || ctl_get_prkey(lun, i) == 0)
					continue;

				ctl_clr_prkey(lun, i);
				ctl_est_ua(lun, i, CTL_UA_REG_PREEMPT);
			}
			lun->pr_key_count = 1;
			lun->pr_res_type = type;
			if (lun->pr_res_type != SPR_TYPE_WR_EX_AR &&
			    lun->pr_res_type != SPR_TYPE_EX_AC_AR)
				lun->pr_res_idx = residx;
			lun->pr_generation++;
			mtx_unlock(&lun->lun_lock);

			/* send msg to other side */
			persis_io.hdr.nexus = ctsio->io_hdr.nexus;
			persis_io.hdr.msg_type = CTL_MSG_PERS_ACTION;
			persis_io.pr.pr_info.action = CTL_PR_PREEMPT;
			persis_io.pr.pr_info.residx = lun->pr_res_idx;
			persis_io.pr.pr_info.res_type = type;
			memcpy(persis_io.pr.pr_info.sa_res_key,
			       param->serv_act_res_key,
			       sizeof(param->serv_act_res_key));
			ctl_ha_msg_send(CTL_HA_CHAN_CTL, &persis_io,
			    sizeof(persis_io.pr), M_WAITOK);
		} else {
			/* not all registrants */
			mtx_unlock(&lun->lun_lock);
			free(ctsio->kern_data_ptr, M_CTL);
			ctl_set_invalid_field(ctsio,
					      /*sks_valid*/ 1,
					      /*command*/ 0,
					      /*field*/ 8,
					      /*bit_valid*/ 0,
					      /*bit*/ 0);
			ctl_done((union ctl_io *)ctsio);
			return (1);
		}
	} else if (lun->pr_res_idx == CTL_PR_ALL_REGISTRANTS
		|| !(lun->flags & CTL_LUN_PR_RESERVED)) {
		int found = 0;

		if (res_key == sa_res_key) {
			/* special case */
			/*
			 * The spec implies this is not good but doesn't
			 * say what to do. There are two choices either
			 * generate a res conflict or check condition
			 * with illegal field in parameter data. Since
			 * that is what is done when the sa_res_key is
			 * zero I'll take that approach since this has
			 * to do with the sa_res_key.
			 */
			mtx_unlock(&lun->lun_lock);
			free(ctsio->kern_data_ptr, M_CTL);
			ctl_set_invalid_field(ctsio,
					      /*sks_valid*/ 1,
					      /*command*/ 0,
					      /*field*/ 8,
					      /*bit_valid*/ 0,
					      /*bit*/ 0);
			ctl_done((union ctl_io *)ctsio);
			return (1);
		}

		for (i = 0; i < CTL_MAX_INITIATORS; i++) {
			if (ctl_get_prkey(lun, i) != sa_res_key)
				continue;

			found = 1;
			ctl_clr_prkey(lun, i);
			lun->pr_key_count--;
			ctl_est_ua(lun, i, CTL_UA_REG_PREEMPT);
		}
		if (!found) {
			mtx_unlock(&lun->lun_lock);
			free(ctsio->kern_data_ptr, M_CTL);
			ctl_set_reservation_conflict(ctsio);
			ctl_done((union ctl_io *)ctsio);
			return (CTL_RETVAL_COMPLETE);
		}
		lun->pr_generation++;
		mtx_unlock(&lun->lun_lock);

		/* send msg to other side */
		persis_io.hdr.nexus = ctsio->io_hdr.nexus;
		persis_io.hdr.msg_type = CTL_MSG_PERS_ACTION;
		persis_io.pr.pr_info.action = CTL_PR_PREEMPT;
		persis_io.pr.pr_info.residx = lun->pr_res_idx;
		persis_io.pr.pr_info.res_type = type;
		memcpy(persis_io.pr.pr_info.sa_res_key,
		       param->serv_act_res_key,
		       sizeof(param->serv_act_res_key));
		ctl_ha_msg_send(CTL_HA_CHAN_CTL, &persis_io,
		    sizeof(persis_io.pr), M_WAITOK);
	} else {
		/* Reserved but not all registrants */
		/* sa_res_key is res holder */
		if (sa_res_key == ctl_get_prkey(lun, lun->pr_res_idx)) {
			/* validate scope and type */
			if ((cdb->scope_type & SPR_SCOPE_MASK) !=
			     SPR_LU_SCOPE) {
				mtx_unlock(&lun->lun_lock);
				ctl_set_invalid_field(/*ctsio*/ ctsio,
						      /*sks_valid*/ 1,
						      /*command*/ 1,
						      /*field*/ 2,
						      /*bit_valid*/ 1,
						      /*bit*/ 4);
				ctl_done((union ctl_io *)ctsio);
				return (1);
			}

			if (type>8 || type==2 || type==4 || type==0) {
				mtx_unlock(&lun->lun_lock);
				ctl_set_invalid_field(/*ctsio*/ ctsio,
						      /*sks_valid*/ 1,
						      /*command*/ 1,
						      /*field*/ 2,
						      /*bit_valid*/ 1,
						      /*bit*/ 0);
				ctl_done((union ctl_io *)ctsio);
				return (1);
			}

			/*
			 * Do the following:
			 * if sa_res_key != res_key remove all
			 * registrants w/sa_res_key and generate UA
			 * for these registrants(Registrations
			 * Preempted) if it wasn't an exclusive
			 * reservation generate UA(Reservations
			 * Preempted) for all other registered nexuses
			 * if the type has changed. Establish the new
			 * reservation and holder. If res_key and
			 * sa_res_key are the same do the above
			 * except don't unregister the res holder.
			 */

			for(i = 0; i < CTL_MAX_INITIATORS; i++) {
				if (i == residx || ctl_get_prkey(lun, i) == 0)
					continue;

				if (sa_res_key == ctl_get_prkey(lun, i)) {
					ctl_clr_prkey(lun, i);
					lun->pr_key_count--;
					ctl_est_ua(lun, i, CTL_UA_REG_PREEMPT);
				} else if (type != lun->pr_res_type &&
				    (lun->pr_res_type == SPR_TYPE_WR_EX_RO ||
				     lun->pr_res_type == SPR_TYPE_EX_AC_RO)) {
					ctl_est_ua(lun, i, CTL_UA_RES_RELEASE);
				}
			}
			lun->pr_res_type = type;
			if (lun->pr_res_type != SPR_TYPE_WR_EX_AR &&
			    lun->pr_res_type != SPR_TYPE_EX_AC_AR)
				lun->pr_res_idx = residx;
			else
				lun->pr_res_idx = CTL_PR_ALL_REGISTRANTS;
			lun->pr_generation++;
			mtx_unlock(&lun->lun_lock);

			persis_io.hdr.nexus = ctsio->io_hdr.nexus;
			persis_io.hdr.msg_type = CTL_MSG_PERS_ACTION;
			persis_io.pr.pr_info.action = CTL_PR_PREEMPT;
			persis_io.pr.pr_info.residx = lun->pr_res_idx;
			persis_io.pr.pr_info.res_type = type;
			memcpy(persis_io.pr.pr_info.sa_res_key,
			       param->serv_act_res_key,
			       sizeof(param->serv_act_res_key));
			ctl_ha_msg_send(CTL_HA_CHAN_CTL, &persis_io,
			    sizeof(persis_io.pr), M_WAITOK);
		} else {
			/*
			 * sa_res_key is not the res holder just
			 * remove registrants
			 */
			int found=0;

			for (i = 0; i < CTL_MAX_INITIATORS; i++) {
				if (sa_res_key != ctl_get_prkey(lun, i))
					continue;

				found = 1;
				ctl_clr_prkey(lun, i);
				lun->pr_key_count--;
				ctl_est_ua(lun, i, CTL_UA_REG_PREEMPT);
			}

			if (!found) {
				mtx_unlock(&lun->lun_lock);
				free(ctsio->kern_data_ptr, M_CTL);
				ctl_set_reservation_conflict(ctsio);
				ctl_done((union ctl_io *)ctsio);
		        	return (1);
			}
			lun->pr_generation++;
			mtx_unlock(&lun->lun_lock);

			persis_io.hdr.nexus = ctsio->io_hdr.nexus;
			persis_io.hdr.msg_type = CTL_MSG_PERS_ACTION;
			persis_io.pr.pr_info.action = CTL_PR_PREEMPT;
			persis_io.pr.pr_info.residx = lun->pr_res_idx;
			persis_io.pr.pr_info.res_type = type;
			memcpy(persis_io.pr.pr_info.sa_res_key,
			       param->serv_act_res_key,
			       sizeof(param->serv_act_res_key));
			ctl_ha_msg_send(CTL_HA_CHAN_CTL, &persis_io,
			    sizeof(persis_io.pr), M_WAITOK);
		}
	}
	return (0);
}