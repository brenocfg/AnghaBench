#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ispsoftc_t ;
struct TYPE_4__ {int /*<<< orphan*/  pdb_sl_ptr; int /*<<< orphan*/  pdb_il_ptr; int /*<<< orphan*/  pdb_loopid; int /*<<< orphan*/  pdb_prli_svc3; int /*<<< orphan*/  pdb_prli_svc0; int /*<<< orphan*/  pdb_prli_len; int /*<<< orphan*/  pdb_fcount; int /*<<< orphan*/  pdb_nxt_seqid; int /*<<< orphan*/  pdb_ptimer; int /*<<< orphan*/  pdb_sqtail; int /*<<< orphan*/  pdb_sqhead; int /*<<< orphan*/  pdb_lstopflg; int /*<<< orphan*/  pdb_labrtflg; int /*<<< orphan*/  pdb_noseq; int /*<<< orphan*/  pdb_ncseq; int /*<<< orphan*/  pdb_rdsiz; int /*<<< orphan*/  pdb_initiator; int /*<<< orphan*/  pdb_target; int /*<<< orphan*/  pdb_roi; int /*<<< orphan*/  pdb_pconcurrnt; int /*<<< orphan*/  pdb_features; int /*<<< orphan*/  pdb_tl_last; int /*<<< orphan*/  pdb_tl_next; int /*<<< orphan*/  pdb_qtail; int /*<<< orphan*/  pdb_qhead; int /*<<< orphan*/  pdb_curalloc; int /*<<< orphan*/  pdb_resalloc; int /*<<< orphan*/  pdb_retry_delay; int /*<<< orphan*/  pdb_retry_count; int /*<<< orphan*/  pdb_exec_count; int /*<<< orphan*/  pdb_execthrottle; int /*<<< orphan*/ * pdb_portname; int /*<<< orphan*/ * pdb_nodename; int /*<<< orphan*/ * pdb_portid_bits; int /*<<< orphan*/ * pdb_hardaddr_bits; int /*<<< orphan*/  pdb_sstate; int /*<<< orphan*/  pdb_mstate; int /*<<< orphan*/  pdb_options; } ;
typedef  TYPE_1__ isp_pdb_21xx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_IOXGET_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISP_IOXGET_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
isp_get_pdb_21xx(ispsoftc_t *isp, isp_pdb_21xx_t *src, isp_pdb_21xx_t *dst)
{
	int i;
	ISP_IOXGET_16(isp, &src->pdb_options, dst->pdb_options);
        ISP_IOXGET_8(isp, &src->pdb_mstate, dst->pdb_mstate);
        ISP_IOXGET_8(isp, &src->pdb_sstate, dst->pdb_sstate);
	for (i = 0; i < 4; i++) {
		ISP_IOXGET_8(isp, &src->pdb_hardaddr_bits[i], dst->pdb_hardaddr_bits[i]);
	}
	for (i = 0; i < 4; i++) {
		ISP_IOXGET_8(isp, &src->pdb_portid_bits[i], dst->pdb_portid_bits[i]);
	}
	for (i = 0; i < 8; i++) {
		ISP_IOXGET_8(isp, &src->pdb_nodename[i], dst->pdb_nodename[i]);
	}
	for (i = 0; i < 8; i++) {
		ISP_IOXGET_8(isp, &src->pdb_portname[i], dst->pdb_portname[i]);
	}
	ISP_IOXGET_16(isp, &src->pdb_execthrottle, dst->pdb_execthrottle);
	ISP_IOXGET_16(isp, &src->pdb_exec_count, dst->pdb_exec_count);
	ISP_IOXGET_8(isp, &src->pdb_retry_count, dst->pdb_retry_count);
	ISP_IOXGET_8(isp, &src->pdb_retry_delay, dst->pdb_retry_delay);
	ISP_IOXGET_16(isp, &src->pdb_resalloc, dst->pdb_resalloc);
	ISP_IOXGET_16(isp, &src->pdb_curalloc, dst->pdb_curalloc);
	ISP_IOXGET_16(isp, &src->pdb_qhead, dst->pdb_qhead);
	ISP_IOXGET_16(isp, &src->pdb_qtail, dst->pdb_qtail);
	ISP_IOXGET_16(isp, &src->pdb_tl_next, dst->pdb_tl_next);
	ISP_IOXGET_16(isp, &src->pdb_tl_last, dst->pdb_tl_last);
	ISP_IOXGET_16(isp, &src->pdb_features, dst->pdb_features);
	ISP_IOXGET_16(isp, &src->pdb_pconcurrnt, dst->pdb_pconcurrnt);
	ISP_IOXGET_16(isp, &src->pdb_roi, dst->pdb_roi);
	ISP_IOXGET_8(isp, &src->pdb_target, dst->pdb_target);
	ISP_IOXGET_8(isp, &src->pdb_initiator, dst->pdb_initiator);
	ISP_IOXGET_16(isp, &src->pdb_rdsiz, dst->pdb_rdsiz);
	ISP_IOXGET_16(isp, &src->pdb_ncseq, dst->pdb_ncseq);
	ISP_IOXGET_16(isp, &src->pdb_noseq, dst->pdb_noseq);
	ISP_IOXGET_16(isp, &src->pdb_labrtflg, dst->pdb_labrtflg);
	ISP_IOXGET_16(isp, &src->pdb_lstopflg, dst->pdb_lstopflg);
	ISP_IOXGET_16(isp, &src->pdb_sqhead, dst->pdb_sqhead);
	ISP_IOXGET_16(isp, &src->pdb_sqtail, dst->pdb_sqtail);
	ISP_IOXGET_16(isp, &src->pdb_ptimer, dst->pdb_ptimer);
	ISP_IOXGET_16(isp, &src->pdb_nxt_seqid, dst->pdb_nxt_seqid);
	ISP_IOXGET_16(isp, &src->pdb_fcount, dst->pdb_fcount);
	ISP_IOXGET_16(isp, &src->pdb_prli_len, dst->pdb_prli_len);
	ISP_IOXGET_16(isp, &src->pdb_prli_svc0, dst->pdb_prli_svc0);
	ISP_IOXGET_16(isp, &src->pdb_prli_svc3, dst->pdb_prli_svc3);
	ISP_IOXGET_16(isp, &src->pdb_loopid, dst->pdb_loopid);
	ISP_IOXGET_16(isp, &src->pdb_il_ptr, dst->pdb_il_ptr);
	ISP_IOXGET_16(isp, &src->pdb_sl_ptr, dst->pdb_sl_ptr);
}