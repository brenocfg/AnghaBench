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
struct TYPE_2__ {int /*<<< orphan*/  done; } ;
union cptx_vqx_done {TYPE_1__ s; int /*<<< orphan*/  u; } ;
typedef  int /*<<< orphan*/  u32 ;
struct cpt_vf {int /*<<< orphan*/  reg_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPTX_VQX_DONE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpt_read_csr64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 cptvf_read_vq_done_count(struct cpt_vf *cptvf)
{
	union cptx_vqx_done vqx_done;

	vqx_done.u = cpt_read_csr64(cptvf->reg_base, CPTX_VQX_DONE(0, 0));
	return vqx_done.s.done;
}