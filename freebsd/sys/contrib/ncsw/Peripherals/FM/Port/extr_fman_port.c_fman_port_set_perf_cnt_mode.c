#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct fman_port {int type; TYPE_4__* bmi_regs; } ;
struct TYPE_5__ {int /*<<< orphan*/  fmbm_opc; } ;
struct TYPE_7__ {int /*<<< orphan*/  fmbm_tpc; } ;
struct TYPE_6__ {int /*<<< orphan*/  fmbm_rpc; } ;
struct TYPE_8__ {TYPE_1__ oh; TYPE_3__ tx; TYPE_2__ rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMI_COUNTERS_EN ; 
 int EINVAL ; 
#define  E_FMAN_PORT_TYPE_HC 133 
#define  E_FMAN_PORT_TYPE_OP 132 
#define  E_FMAN_PORT_TYPE_RX 131 
#define  E_FMAN_PORT_TYPE_RX_10G 130 
#define  E_FMAN_PORT_TYPE_TX 129 
#define  E_FMAN_PORT_TYPE_TX_10G 128 
 int /*<<< orphan*/  ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int fman_port_set_perf_cnt_mode(struct fman_port *port, bool enable)
{
    uint32_t *stats_reg, tmp;

    switch (port->type) {
    case E_FMAN_PORT_TYPE_RX:
    case E_FMAN_PORT_TYPE_RX_10G:
        stats_reg = &port->bmi_regs->rx.fmbm_rpc;
        break;
    case E_FMAN_PORT_TYPE_TX:
    case E_FMAN_PORT_TYPE_TX_10G:
        stats_reg = &port->bmi_regs->tx.fmbm_tpc;
        break;
    case E_FMAN_PORT_TYPE_OP:
    case E_FMAN_PORT_TYPE_HC:
        stats_reg = &port->bmi_regs->oh.fmbm_opc;
        break;
    default:
        return -EINVAL;
    }

    tmp = ioread32be(stats_reg);

    if (enable)
        tmp |= BMI_COUNTERS_EN;
    else
        tmp &= ~BMI_COUNTERS_EN;

    iowrite32be(tmp, stats_reg);
    return 0;
}