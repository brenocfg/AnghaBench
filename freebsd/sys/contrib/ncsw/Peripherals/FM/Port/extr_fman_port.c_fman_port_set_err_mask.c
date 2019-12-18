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
struct TYPE_5__ {int /*<<< orphan*/  fmbm_ofsem; } ;
struct TYPE_4__ {int /*<<< orphan*/  fmbm_rfsem; } ;
struct TYPE_6__ {TYPE_2__ oh; TYPE_1__ rx; } ;

/* Variables and functions */
 int EINVAL ; 
#define  E_FMAN_PORT_TYPE_OP 130 
#define  E_FMAN_PORT_TYPE_RX 129 
#define  E_FMAN_PORT_TYPE_RX_10G 128 
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int fman_port_set_err_mask(struct fman_port *port, uint32_t err_mask)
{
    uint32_t *err_mask_reg;

    /* Obtain register address */
    switch (port->type) {
    case E_FMAN_PORT_TYPE_RX:
    case E_FMAN_PORT_TYPE_RX_10G:
        err_mask_reg = &port->bmi_regs->rx.fmbm_rfsem;
        break;
    case E_FMAN_PORT_TYPE_OP:
        err_mask_reg = &port->bmi_regs->oh.fmbm_ofsem;
        break;
    default:
        return -EINVAL;
    }

    iowrite32be(err_mask, err_mask_reg);
    return 0;
}