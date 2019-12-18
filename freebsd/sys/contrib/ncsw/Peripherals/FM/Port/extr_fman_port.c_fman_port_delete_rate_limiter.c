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
typedef  int /*<<< orphan*/  uint32_t ;
struct fman_port {int type; TYPE_3__* bmi_regs; } ;
struct TYPE_5__ {int /*<<< orphan*/  fmbm_orlmts; } ;
struct TYPE_4__ {int /*<<< orphan*/  fmbm_trlmts; } ;
struct TYPE_6__ {TYPE_2__ oh; TYPE_1__ tx; } ;

/* Variables and functions */
 int EINVAL ; 
#define  E_FMAN_PORT_TYPE_OP 130 
#define  E_FMAN_PORT_TYPE_TX 129 
#define  E_FMAN_PORT_TYPE_TX_10G 128 
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int fman_port_delete_rate_limiter(struct fman_port *port)
{
    uint32_t *rate_limit_scale_reg;

    switch (port->type) {
    case E_FMAN_PORT_TYPE_TX:
    case E_FMAN_PORT_TYPE_TX_10G:
        rate_limit_scale_reg = &port->bmi_regs->tx.fmbm_trlmts;
        break;
    case E_FMAN_PORT_TYPE_OP:
        rate_limit_scale_reg = &port->bmi_regs->oh.fmbm_orlmts;
        break;
    default:
        return -EINVAL;
    }

    iowrite32be(0, rate_limit_scale_reg);
    return 0;
}