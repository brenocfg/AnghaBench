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
struct TYPE_2__ {int cont_err; int /*<<< orphan*/  size; } ;
union cptx_pf_qx_ctl {int /*<<< orphan*/  u; TYPE_1__ s; } ;
typedef  int /*<<< orphan*/  u32 ;
struct cpt_device {int /*<<< orphan*/  reg_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPTX_PF_QX_CTL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpt_read_csr64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpt_write_csr64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpt_cfg_qlen_for_vf(struct cpt_device *cpt, int vf, u32 size)
{
	union cptx_pf_qx_ctl pf_qx_ctl;

	pf_qx_ctl.u = cpt_read_csr64(cpt->reg_base, CPTX_PF_QX_CTL(0, vf));
	pf_qx_ctl.s.size = size;
	pf_qx_ctl.s.cont_err = true;
	cpt_write_csr64(cpt->reg_base, CPTX_PF_QX_CTL(0, vf), pf_qx_ctl.u);
}