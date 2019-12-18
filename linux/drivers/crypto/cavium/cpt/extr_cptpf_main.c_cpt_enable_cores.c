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
typedef  scalar_t__ u8 ;
typedef  int u64 ;
struct cpt_device {int max_se_cores; int /*<<< orphan*/  reg_base; } ;

/* Variables and functions */
 scalar_t__ AE_TYPES ; 
 int /*<<< orphan*/  CPTX_PF_EXE_CTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_DELAY ; 
 int cpt_read_csr64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpt_write_csr64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpt_enable_cores(struct cpt_device *cpt, u64 coremask,
			     u8 type)
{
	u64 pf_exe_ctl;

	if (type == AE_TYPES)
		coremask = (coremask << cpt->max_se_cores);

	pf_exe_ctl = cpt_read_csr64(cpt->reg_base, CPTX_PF_EXE_CTL(0));
	cpt_write_csr64(cpt->reg_base, CPTX_PF_EXE_CTL(0),
			(pf_exe_ctl | coremask));
	udelay(CSR_DELAY);
}