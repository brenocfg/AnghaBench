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
struct TYPE_2__ {int /*<<< orphan*/  ae; int /*<<< orphan*/  se; } ;
union cptx_pf_constants {TYPE_1__ s; int /*<<< orphan*/  u; int /*<<< orphan*/  member_0; } ;
struct cpt_device {int /*<<< orphan*/  max_ae_cores; int /*<<< orphan*/  max_se_cores; int /*<<< orphan*/  reg_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPTX_PF_CONSTANTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpt_read_csr64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpt_find_max_enabled_cores(struct cpt_device *cpt)
{
	union cptx_pf_constants pf_cnsts = {0};

	pf_cnsts.u = cpt_read_csr64(cpt->reg_base, CPTX_PF_CONSTANTS(0));
	cpt->max_se_cores = pf_cnsts.s.se;
	cpt->max_ae_cores = pf_cnsts.s.ae;
}