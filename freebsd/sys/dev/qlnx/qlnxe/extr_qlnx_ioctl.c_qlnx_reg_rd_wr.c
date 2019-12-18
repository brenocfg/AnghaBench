#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ecore_hwfn {int dummy; } ;
struct TYPE_7__ {size_t hwfn_index; int cmd; int /*<<< orphan*/  val; int /*<<< orphan*/  addr; int /*<<< orphan*/  access_type; } ;
typedef  TYPE_2__ qlnx_reg_rd_wr_t ;
struct TYPE_6__ {struct ecore_hwfn* hwfns; } ;
struct TYPE_8__ {TYPE_1__ cdev; } ;
typedef  TYPE_3__ qlnx_host_t ;

/* Variables and functions */
 int EINVAL ; 
 size_t QLNX_MAX_HW_FUNCS ; 
 int /*<<< orphan*/  QLNX_REG_ACCESS_DIRECT ; 
#define  QLNX_REG_READ_CMD 129 
#define  QLNX_REG_WRITE_CMD 128 
 int /*<<< orphan*/  qlnx_reg_rd32 (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlnx_reg_wr32 (struct ecore_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qlnx_reg_rd_wr(qlnx_host_t *ha, qlnx_reg_rd_wr_t *reg_rd_wr)
{
	int			rval = 0;
	struct ecore_hwfn	*p_hwfn;

	if (reg_rd_wr->hwfn_index >= QLNX_MAX_HW_FUNCS) {
		return (EINVAL);
	}

	p_hwfn = &ha->cdev.hwfns[reg_rd_wr->hwfn_index];

	switch (reg_rd_wr->cmd) {

		case QLNX_REG_READ_CMD:
			if (reg_rd_wr->access_type == QLNX_REG_ACCESS_DIRECT) {
				reg_rd_wr->val = qlnx_reg_rd32(p_hwfn,
							reg_rd_wr->addr);
			}
			break;

		case QLNX_REG_WRITE_CMD:
			if (reg_rd_wr->access_type == QLNX_REG_ACCESS_DIRECT) {
				qlnx_reg_wr32(p_hwfn, reg_rd_wr->addr,
					reg_rd_wr->val);
			}
			break;

		default:
			rval = EINVAL;
			break;
	} 

	return (rval);
}