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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct pfvf_def_resp_tlv {int dummy; } ;
struct ecore_vf_info {int dummy; } ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_TLV_CLOSE ; 
 int /*<<< orphan*/  PFVF_STATUS_SUCCESS ; 
 int /*<<< orphan*/  ecore_iov_config_perm_table (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_vf_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_iov_prepare_resp (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_vf_info*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_iov_vf_igu_set_int (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_vf_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ecore_iov_vf_mbx_close(struct ecore_hwfn *p_hwfn,
				   struct ecore_ptt *p_ptt,
				   struct ecore_vf_info	*vf)
{
	u16                      length = sizeof(struct pfvf_def_resp_tlv);
	u8                       status = PFVF_STATUS_SUCCESS;

	/* Disable Interrupts for VF */
	ecore_iov_vf_igu_set_int(p_hwfn, p_ptt, vf, 0);

	/* Reset Permission table */
	ecore_iov_config_perm_table(p_hwfn, p_ptt, vf, 0);

	ecore_iov_prepare_resp(p_hwfn, p_ptt, vf, CHANNEL_TLV_CLOSE,
			       length, status);
}