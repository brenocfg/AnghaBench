#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct fman_port {int type; int fm_rev_maj; TYPE_3__* bmi_regs; } ;
struct TYPE_5__ {int /*<<< orphan*/ * fmbm_ocgm; } ;
struct TYPE_4__ {int /*<<< orphan*/ * fmbm_rcgm; } ;
struct TYPE_6__ {TYPE_2__ oh; TYPE_1__ rx; } ;

/* Variables and functions */
 int EINVAL ; 
#define  E_FMAN_PORT_TYPE_OP 130 
#define  E_FMAN_PORT_TYPE_RX 129 
#define  E_FMAN_PORT_TYPE_RX_10G 128 
 int FMAN_PORT_CG_MAP_NUM ; 
 int /*<<< orphan*/  ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int fman_port_remove_congestion_grps(struct fman_port *port,
        uint32_t grps_map[FMAN_PORT_CG_MAP_NUM])
{
    int i;
    uint32_t tmp, *grp_map_reg;
    uint8_t max_grp_map_num;

    switch (port->type) {
    case E_FMAN_PORT_TYPE_RX:
    case E_FMAN_PORT_TYPE_RX_10G:
        if (port->fm_rev_maj == 4)
            max_grp_map_num = 1;
        else
            max_grp_map_num = FMAN_PORT_CG_MAP_NUM;
        grp_map_reg = port->bmi_regs->rx.fmbm_rcgm;
        break;
    case E_FMAN_PORT_TYPE_OP:
        max_grp_map_num = 1;
        if (port->fm_rev_maj != 4)
            return -EINVAL;
        grp_map_reg = port->bmi_regs->oh.fmbm_ocgm;
        break;
    default:
        return -EINVAL;
    }

    for (i = (max_grp_map_num - 1); i >= 0; i--) {
        if (grps_map[i] == 0)
            continue;
        tmp = ioread32be(&grp_map_reg[i]);
        tmp &= ~grps_map[i];
        iowrite32be(tmp, &grp_map_reg[i]);
    }
    return 0;
}