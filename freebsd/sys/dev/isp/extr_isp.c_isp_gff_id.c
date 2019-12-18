#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_11__ {scalar_t__ ct_cmd_resp; } ;
struct TYPE_12__ {scalar_t__* snscb_fc4_features; TYPE_1__ snscb_cthdr; } ;
typedef  TYPE_2__ sns_gff_id_rsp_t ;
typedef  int /*<<< orphan*/  ispsoftc_t ;
struct TYPE_13__ {int /*<<< orphan*/  isp_use_gff_id; int /*<<< orphan*/ * isp_scratch; } ;
typedef  TYPE_3__ fcparam ;
struct TYPE_14__ {int ct_bcnt_resid; int /*<<< orphan*/  ct_cmd_resp; int /*<<< orphan*/  ct_fcs_subtype; int /*<<< orphan*/  ct_fcs_type; int /*<<< orphan*/  ct_revision; } ;
typedef  TYPE_4__ ct_hdr_t ;
typedef  int /*<<< orphan*/  ct ;

/* Variables and functions */
 int /*<<< orphan*/  CT_FC_SUBTYPE_NS ; 
 int /*<<< orphan*/  CT_FC_TYPE_FC ; 
 int /*<<< orphan*/  CT_REVISION ; 
 int FC4_SCSI ; 
 TYPE_3__* FCPARAM (int /*<<< orphan*/ *,int) ; 
 scalar_t__ FC_SCRATCH_ACQUIRE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FC_SCRATCH_RELEASE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ISP_IOZPUT_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_LOGDEBUG0 ; 
 int /*<<< orphan*/  ISP_LOGERR ; 
 int /*<<< orphan*/  ISP_MEMZERO (TYPE_4__*,int) ; 
 int ISP_SWAP32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IS_24XX (int /*<<< orphan*/ *) ; 
 scalar_t__ LS_ACC ; 
 int /*<<< orphan*/  SNS_GFF_ID ; 
 int SNS_GFF_ID_RESP_SIZE ; 
 scalar_t__ isp_ct_passthru (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  isp_get_gff_id_response (int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  isp_prt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  isp_put_ct_hdr (int /*<<< orphan*/ *,TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  sacq ; 

__attribute__((used)) static int
isp_gff_id(ispsoftc_t *isp, int chan, uint32_t portid)
{
	fcparam *fcp = FCPARAM(isp, chan);
	ct_hdr_t ct;
	uint32_t *rp;
	uint8_t *scp = fcp->isp_scratch;
	sns_gff_id_rsp_t rsp;
	int i, res = -1;

	if (!fcp->isp_use_gff_id)	/* User may block GFF_ID use. */
		return (res);

	if (!IS_24XX(isp))	/* Old chips can't request GFF_ID. */
		return (res);

	isp_prt(isp, ISP_LOGDEBUG0, "Chan %d requesting GFF_ID", chan);
	if (FC_SCRATCH_ACQUIRE(isp, chan)) {
		isp_prt(isp, ISP_LOGERR, sacq);
		return (res);
	}

	/* Build the CT command and execute via pass-through. */
	ISP_MEMZERO(&ct, sizeof (ct));
	ct.ct_revision = CT_REVISION;
	ct.ct_fcs_type = CT_FC_TYPE_FC;
	ct.ct_fcs_subtype = CT_FC_SUBTYPE_NS;
	ct.ct_cmd_resp = SNS_GFF_ID;
	ct.ct_bcnt_resid = (SNS_GFF_ID_RESP_SIZE - sizeof(ct)) / 4;
	isp_put_ct_hdr(isp, &ct, (ct_hdr_t *)scp);
	rp = (uint32_t *) &scp[sizeof(ct)];
	ISP_IOZPUT_32(isp, portid, rp);

	if (isp_ct_passthru(isp, chan, sizeof(ct) + sizeof(uint32_t),
	    SNS_GFF_ID_RESP_SIZE)) {
		FC_SCRATCH_RELEASE(isp, chan);
		return (res);
	}

	isp_get_gff_id_response(isp, (sns_gff_id_rsp_t *)scp, &rsp);
	if (rsp.snscb_cthdr.ct_cmd_resp == LS_ACC) {
		for (i = 0; i < 32; i++) {
			if (rsp.snscb_fc4_features[i] != 0) {
				res = 0;
				break;
			}
		}
		if (((rsp.snscb_fc4_features[FC4_SCSI / 8] >>
		    ((FC4_SCSI % 8) * 4)) & 0x01) != 0)
			res = 1;
		/* Workaround for broken Brocade firmware. */
		if (((ISP_SWAP32(isp, rsp.snscb_fc4_features[FC4_SCSI / 8]) >>
		    ((FC4_SCSI % 8) * 4)) & 0x01) != 0)
			res = 1;
	}
	FC_SCRATCH_RELEASE(isp, chan);
	isp_prt(isp, ISP_LOGDEBUG0, "Chan %d GFF_ID result is %d", chan, res);
	return (res);
}