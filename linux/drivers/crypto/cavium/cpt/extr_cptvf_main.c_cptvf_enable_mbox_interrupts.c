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
struct TYPE_2__ {int mbox; } ;
union cptx_vqx_misc_ena_w1s {int /*<<< orphan*/  u; TYPE_1__ s; } ;
struct cpt_vf {int /*<<< orphan*/  reg_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPTX_VQX_MISC_ENA_W1S (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpt_read_csr64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpt_write_csr64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cptvf_enable_mbox_interrupts(struct cpt_vf *cptvf)
{
	union cptx_vqx_misc_ena_w1s vqx_misc_ena;

	vqx_misc_ena.u = cpt_read_csr64(cptvf->reg_base,
					CPTX_VQX_MISC_ENA_W1S(0, 0));
	/* Set mbox(0) interupts for the requested vf */
	vqx_misc_ena.s.mbox = 1;
	cpt_write_csr64(cptvf->reg_base, CPTX_VQX_MISC_ENA_W1S(0, 0),
			vqx_misc_ena.u);
}