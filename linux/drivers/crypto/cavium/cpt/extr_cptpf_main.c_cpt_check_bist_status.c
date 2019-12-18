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
union cptx_pf_bist_status {int /*<<< orphan*/  u; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  u32 ;
struct cpt_device {int /*<<< orphan*/  reg_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPTX_PF_BIST_STATUS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpt_read_csr64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 cpt_check_bist_status(struct cpt_device *cpt)
{
	union cptx_pf_bist_status bist_sts = {0};

	bist_sts.u = cpt_read_csr64(cpt->reg_base,
				    CPTX_PF_BIST_STATUS(0));

	return bist_sts.u;
}