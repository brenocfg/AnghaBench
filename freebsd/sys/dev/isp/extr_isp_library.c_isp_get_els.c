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
struct TYPE_4__ {int /*<<< orphan*/ * els_reserved4; int /*<<< orphan*/  els_subcode2; int /*<<< orphan*/  els_subcode1; int /*<<< orphan*/  els_bytecnt; int /*<<< orphan*/  els_ctl_flags; int /*<<< orphan*/  els_reserved3; int /*<<< orphan*/  els_reserved2; int /*<<< orphan*/  els_did_hi; int /*<<< orphan*/  els_did_mid; int /*<<< orphan*/  els_did_lo; int /*<<< orphan*/  els_reserved1; int /*<<< orphan*/  els_opcode; int /*<<< orphan*/  els_recv_dsd_count; int /*<<< orphan*/  els_rxid; int /*<<< orphan*/  els_sof; int /*<<< orphan*/  els_vphdl; int /*<<< orphan*/  els_xmit_dsd_count; int /*<<< orphan*/  els_nphdl; int /*<<< orphan*/  els_status; int /*<<< orphan*/  els_handle; int /*<<< orphan*/  els_hdr; } ;
typedef  TYPE_1__ els_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_IOXGET_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISP_IOXGET_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISP_IOXGET_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_get_hdr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
isp_get_els(ispsoftc_t *isp, els_t *src, els_t *dst)
{
	int i;

	isp_get_hdr(isp, &src->els_hdr, &dst->els_hdr);
	ISP_IOXGET_32(isp, &src->els_handle, dst->els_handle);
	ISP_IOXGET_16(isp, &src->els_status, dst->els_status);
	ISP_IOXGET_16(isp, &src->els_nphdl, dst->els_nphdl);
	ISP_IOXGET_16(isp, &src->els_xmit_dsd_count, dst->els_xmit_dsd_count);
	ISP_IOXGET_8(isp, &src->els_vphdl, dst->els_vphdl);
	ISP_IOXGET_8(isp, &src->els_sof, dst->els_sof);
	ISP_IOXGET_32(isp, &src->els_rxid, dst->els_rxid);
	ISP_IOXGET_16(isp, &src->els_recv_dsd_count, dst->els_recv_dsd_count);
	ISP_IOXGET_8(isp, &src->els_opcode, dst->els_opcode);
	ISP_IOXGET_8(isp, &src->els_reserved2, dst->els_reserved1);
	ISP_IOXGET_8(isp, &src->els_did_lo, dst->els_did_lo);
	ISP_IOXGET_8(isp, &src->els_did_mid, dst->els_did_mid);
	ISP_IOXGET_8(isp, &src->els_did_hi, dst->els_did_hi);
	ISP_IOXGET_8(isp, &src->els_reserved2, dst->els_reserved2);
	ISP_IOXGET_16(isp, &src->els_reserved3, dst->els_reserved3);
	ISP_IOXGET_16(isp, &src->els_ctl_flags, dst->els_ctl_flags);
	ISP_IOXGET_32(isp, &src->els_bytecnt, dst->els_bytecnt);
	ISP_IOXGET_32(isp, &src->els_subcode1, dst->els_subcode1);
	ISP_IOXGET_32(isp, &src->els_subcode2, dst->els_subcode2);
	for (i = 0; i < 20; i++) {
		ISP_IOXGET_8(isp, &src->els_reserved4[i], dst->els_reserved4[i]);
	}
}