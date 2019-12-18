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
struct icp_qat_fw_comn_req_hdr {int /*<<< orphan*/  serv_specif_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICP_QAT_FW_CIPH_IV_64BIT_PTR ; 
 int /*<<< orphan*/  ICP_QAT_FW_LA_CIPH_IV_FLD_FLAG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICP_QAT_FW_LA_UPDATE_STATE ; 
 int /*<<< orphan*/  ICP_QAT_FW_LA_UPDATE_STATE_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qat_alg_init_hdr_iv_updt(struct icp_qat_fw_comn_req_hdr *header)
{
	ICP_QAT_FW_LA_CIPH_IV_FLD_FLAG_SET(header->serv_specif_flags,
					   ICP_QAT_FW_CIPH_IV_64BIT_PTR);
	ICP_QAT_FW_LA_UPDATE_STATE_SET(header->serv_specif_flags,
				       ICP_QAT_FW_LA_UPDATE_STATE);
}