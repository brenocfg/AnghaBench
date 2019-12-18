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
struct al_pcie_port {int /*<<< orphan*/  port_id; int /*<<< orphan*/  rev_id; } ;
struct al_pcie_ib_hcrd_os_ob_reads_config {int /*<<< orphan*/  nof_p_hdr; int /*<<< orphan*/  nof_np_hdr; int /*<<< orphan*/  nof_cpl_hdr; int /*<<< orphan*/  nof_outstanding_ob_reads; } ;

/* Variables and functions */
#define  AL_PCIE_OPERATING_MODE_EP 129 
#define  AL_PCIE_OPERATING_MODE_RC 128 
 int /*<<< orphan*/  AL_PCIE_REV_1_2_EP_NOF_CPL_HDR_DEFAULT ; 
 int /*<<< orphan*/  AL_PCIE_REV_1_2_EP_NOF_NP_HDR_DEFAULT ; 
 int /*<<< orphan*/  AL_PCIE_REV_1_2_EP_NOF_P_HDR_DEFAULT ; 
 int /*<<< orphan*/  AL_PCIE_REV_1_2_EP_OB_OS_READS_DEFAULT ; 
 int /*<<< orphan*/  AL_PCIE_REV_1_2_RC_NOF_CPL_HDR_DEFAULT ; 
 int /*<<< orphan*/  AL_PCIE_REV_1_2_RC_NOF_NP_HDR_DEFAULT ; 
 int /*<<< orphan*/  AL_PCIE_REV_1_2_RC_NOF_P_HDR_DEFAULT ; 
 int /*<<< orphan*/  AL_PCIE_REV_1_2_RC_OB_OS_READS_DEFAULT ; 
 int /*<<< orphan*/  AL_PCIE_REV_3_EP_NOF_CPL_HDR_DEFAULT ; 
 int /*<<< orphan*/  AL_PCIE_REV_3_EP_NOF_NP_HDR_DEFAULT ; 
 int /*<<< orphan*/  AL_PCIE_REV_3_EP_NOF_P_HDR_DEFAULT ; 
 int /*<<< orphan*/  AL_PCIE_REV_3_EP_OB_OS_READS_DEFAULT ; 
 int /*<<< orphan*/  AL_PCIE_REV_3_RC_NOF_CPL_HDR_DEFAULT ; 
 int /*<<< orphan*/  AL_PCIE_REV_3_RC_NOF_NP_HDR_DEFAULT ; 
 int /*<<< orphan*/  AL_PCIE_REV_3_RC_NOF_P_HDR_DEFAULT ; 
 int /*<<< orphan*/  AL_PCIE_REV_3_RC_OB_OS_READS_DEFAULT ; 
 int /*<<< orphan*/  AL_PCIE_REV_ID_3 ; 
 int /*<<< orphan*/  al_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  al_err (char*,int /*<<< orphan*/ ) ; 
 int al_pcie_operating_mode_get (struct al_pcie_port*) ; 
 int /*<<< orphan*/  al_pcie_port_ib_hcrd_os_ob_reads_config (struct al_pcie_port*,struct al_pcie_ib_hcrd_os_ob_reads_config*) ; 

__attribute__((used)) static void
al_pcie_ib_hcrd_os_ob_reads_config_default(
	struct al_pcie_port *pcie_port)
{

	struct al_pcie_ib_hcrd_os_ob_reads_config ib_hcrd_os_ob_reads_config;

	switch (al_pcie_operating_mode_get(pcie_port)) {
	case AL_PCIE_OPERATING_MODE_RC:
		if (pcie_port->rev_id == AL_PCIE_REV_ID_3) {
			ib_hcrd_os_ob_reads_config.nof_outstanding_ob_reads =
				AL_PCIE_REV_3_RC_OB_OS_READS_DEFAULT;
			ib_hcrd_os_ob_reads_config.nof_cpl_hdr =
				AL_PCIE_REV_3_RC_NOF_CPL_HDR_DEFAULT;
			ib_hcrd_os_ob_reads_config.nof_np_hdr =
				AL_PCIE_REV_3_RC_NOF_NP_HDR_DEFAULT;
			ib_hcrd_os_ob_reads_config.nof_p_hdr =
				AL_PCIE_REV_3_RC_NOF_P_HDR_DEFAULT;
		} else {
			ib_hcrd_os_ob_reads_config.nof_outstanding_ob_reads =
				AL_PCIE_REV_1_2_RC_OB_OS_READS_DEFAULT;
			ib_hcrd_os_ob_reads_config.nof_cpl_hdr =
				AL_PCIE_REV_1_2_RC_NOF_CPL_HDR_DEFAULT;
			ib_hcrd_os_ob_reads_config.nof_np_hdr =
				AL_PCIE_REV_1_2_RC_NOF_NP_HDR_DEFAULT;
			ib_hcrd_os_ob_reads_config.nof_p_hdr =
				AL_PCIE_REV_1_2_RC_NOF_P_HDR_DEFAULT;
		}
		break;

	case AL_PCIE_OPERATING_MODE_EP:
		if (pcie_port->rev_id == AL_PCIE_REV_ID_3) {
			ib_hcrd_os_ob_reads_config.nof_outstanding_ob_reads =
				AL_PCIE_REV_3_EP_OB_OS_READS_DEFAULT;
			ib_hcrd_os_ob_reads_config.nof_cpl_hdr =
				AL_PCIE_REV_3_EP_NOF_CPL_HDR_DEFAULT;
			ib_hcrd_os_ob_reads_config.nof_np_hdr =
				AL_PCIE_REV_3_EP_NOF_NP_HDR_DEFAULT;
			ib_hcrd_os_ob_reads_config.nof_p_hdr =
				AL_PCIE_REV_3_EP_NOF_P_HDR_DEFAULT;
		} else {
			ib_hcrd_os_ob_reads_config.nof_outstanding_ob_reads =
				AL_PCIE_REV_1_2_EP_OB_OS_READS_DEFAULT;
			ib_hcrd_os_ob_reads_config.nof_cpl_hdr =
				AL_PCIE_REV_1_2_EP_NOF_CPL_HDR_DEFAULT;
			ib_hcrd_os_ob_reads_config.nof_np_hdr =
				AL_PCIE_REV_1_2_EP_NOF_NP_HDR_DEFAULT;
			ib_hcrd_os_ob_reads_config.nof_p_hdr =
				AL_PCIE_REV_1_2_EP_NOF_P_HDR_DEFAULT;
		}
		break;

	default:
		al_err("PCIe %d: outstanding outbound transactions could not be configured - unknown operating mode\n",
			pcie_port->port_id);
		al_assert(0);
	}

	al_pcie_port_ib_hcrd_os_ob_reads_config(pcie_port, &ib_hcrd_os_ob_reads_config);
}