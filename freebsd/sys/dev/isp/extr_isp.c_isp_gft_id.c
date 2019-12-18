#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_15__ {int ct_bcnt_resid; int snscb_rblen; int snscb_sblen; int snscb_mword_div_2; int /*<<< orphan*/  snscb_portid; void* snscb_cmd; int /*<<< orphan*/ * snscb_addr; void* ct_cmd_resp; int /*<<< orphan*/  ct_fcs_subtype; int /*<<< orphan*/  ct_fcs_type; int /*<<< orphan*/  ct_revision; } ;
typedef  TYPE_2__ sns_gxx_id_req_t ;
struct TYPE_14__ {scalar_t__ ct_cmd_resp; } ;
struct TYPE_16__ {scalar_t__* snscb_fc4_types; TYPE_1__ snscb_cthdr; } ;
typedef  TYPE_3__ sns_gft_id_rsp_t ;
typedef  int /*<<< orphan*/  rq ;
typedef  int /*<<< orphan*/  ispsoftc_t ;
struct TYPE_17__ {int /*<<< orphan*/  isp_scdma; int /*<<< orphan*/  isp_use_gft_id; int /*<<< orphan*/ * isp_scratch; } ;
typedef  TYPE_4__ fcparam ;
typedef  TYPE_2__ ct_hdr_t ;
typedef  int /*<<< orphan*/  ct ;

/* Variables and functions */
 int /*<<< orphan*/  CT_FC_SUBTYPE_NS ; 
 int /*<<< orphan*/  CT_FC_TYPE_FC ; 
 int /*<<< orphan*/  CT_REVISION ; 
 int /*<<< orphan*/  DMA_WD0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_WD1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_WD2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_WD3 (int /*<<< orphan*/ ) ; 
 int FC4_SCSI ; 
 TYPE_4__* FCPARAM (int /*<<< orphan*/ *,int) ; 
 scalar_t__ FC_SCRATCH_ACQUIRE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  FC_SCRATCH_RELEASE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ISP_IOZPUT_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISP_LOGDEBUG0 ; 
 int /*<<< orphan*/  ISP_LOGERR ; 
 int /*<<< orphan*/  ISP_MEMZERO (TYPE_2__*,int) ; 
 scalar_t__ IS_24XX (int /*<<< orphan*/ *) ; 
 scalar_t__ LS_ACC ; 
 size_t RQRSP_ADDR0015 ; 
 size_t RQRSP_ADDR1631 ; 
 size_t RQRSP_ADDR3247 ; 
 size_t RQRSP_ADDR4863 ; 
 void* SNS_GFT_ID ; 
 int SNS_GFT_ID_RESP_SIZE ; 
 int SNS_GXX_ID_REQ_SIZE ; 
 scalar_t__ isp_ct_passthru (int /*<<< orphan*/ *,int,int,int) ; 
 scalar_t__ isp_ct_sns (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  isp_get_gft_id_response (int /*<<< orphan*/ *,TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  isp_prt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  isp_put_ct_hdr (int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  isp_put_gxx_id_request (int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  sacq ; 

__attribute__((used)) static int
isp_gft_id(ispsoftc_t *isp, int chan, uint32_t portid)
{
	fcparam *fcp = FCPARAM(isp, chan);
	ct_hdr_t ct;
	sns_gxx_id_req_t rq;
	uint32_t *rp;
	uint8_t *scp = fcp->isp_scratch;
	sns_gft_id_rsp_t rsp;
	int i, res = -1;

	if (!fcp->isp_use_gft_id)	/* User may block GFT_ID use. */
		return (res);

	isp_prt(isp, ISP_LOGDEBUG0, "Chan %d requesting GFT_ID", chan);
	if (FC_SCRATCH_ACQUIRE(isp, chan)) {
		isp_prt(isp, ISP_LOGERR, sacq);
		return (res);
	}

	if (IS_24XX(isp)) {
		/* Build the CT command and execute via pass-through. */
		ISP_MEMZERO(&ct, sizeof (ct));
		ct.ct_revision = CT_REVISION;
		ct.ct_fcs_type = CT_FC_TYPE_FC;
		ct.ct_fcs_subtype = CT_FC_SUBTYPE_NS;
		ct.ct_cmd_resp = SNS_GFT_ID;
		ct.ct_bcnt_resid = (SNS_GFT_ID_RESP_SIZE - sizeof(ct)) / 4;
		isp_put_ct_hdr(isp, &ct, (ct_hdr_t *)scp);
		rp = (uint32_t *) &scp[sizeof(ct)];
		ISP_IOZPUT_32(isp, portid, rp);

		if (isp_ct_passthru(isp, chan, sizeof(ct) + sizeof(uint32_t),
		    SNS_GFT_ID_RESP_SIZE)) {
			FC_SCRATCH_RELEASE(isp, chan);
			return (res);
		}
	} else {
		/* Build the SNS request and execute via firmware. */
		ISP_MEMZERO(&rq, SNS_GXX_ID_REQ_SIZE);
		rq.snscb_rblen = SNS_GFT_ID_RESP_SIZE >> 1;
		rq.snscb_addr[RQRSP_ADDR0015] = DMA_WD0(fcp->isp_scdma);
		rq.snscb_addr[RQRSP_ADDR1631] = DMA_WD1(fcp->isp_scdma);
		rq.snscb_addr[RQRSP_ADDR3247] = DMA_WD2(fcp->isp_scdma);
		rq.snscb_addr[RQRSP_ADDR4863] = DMA_WD3(fcp->isp_scdma);
		rq.snscb_sblen = 6;
		rq.snscb_cmd = SNS_GFT_ID;
		rq.snscb_mword_div_2 = (SNS_GFT_ID_RESP_SIZE - sizeof(ct)) / 4;
		rq.snscb_portid = portid;
		isp_put_gxx_id_request(isp, &rq, (sns_gxx_id_req_t *)scp);

		if (isp_ct_sns(isp, chan, sizeof(rq), SNS_GFT_ID_RESP_SIZE)) {
			FC_SCRATCH_RELEASE(isp, chan);
			return (res);
		}
	}

	isp_get_gft_id_response(isp, (sns_gft_id_rsp_t *)scp, &rsp);
	if (rsp.snscb_cthdr.ct_cmd_resp == LS_ACC) {
		for (i = 0; i < 8; i++) {
			if (rsp.snscb_fc4_types[i] != 0) {
				res = 0;
				break;
			}
		}
		if (((rsp.snscb_fc4_types[FC4_SCSI / 32] >>
		    (FC4_SCSI % 32)) & 0x01) != 0)
			res = 1;
	}
	FC_SCRATCH_RELEASE(isp, chan);
	isp_prt(isp, ISP_LOGDEBUG0, "Chan %d GFT_ID result is %d", chan, res);
	return (res);
}