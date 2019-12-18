#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct fman_port {int type; size_t ext_pools_num; TYPE_2__* bmi_regs; } ;
struct TYPE_3__ {int /*<<< orphan*/ * fmbm_ebmpi; } ;
struct TYPE_4__ {TYPE_1__ rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMI_EXT_BUF_POOL_EN_COUNTER ; 
 int EINVAL ; 
#define  E_FMAN_PORT_TYPE_RX 129 
#define  E_FMAN_PORT_TYPE_RX_10G 128 
 size_t FMAN_PORT_MAX_EXT_POOLS_NUM ; 
 size_t fman_port_find_bpool (struct fman_port*,size_t) ; 
 int /*<<< orphan*/  ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int fman_port_set_bpool_cnt_mode(struct fman_port *port,
        uint8_t bpid,
        bool enable)
{
    uint8_t index;
    uint32_t tmp;

    switch (port->type) {
    case E_FMAN_PORT_TYPE_RX:
    case E_FMAN_PORT_TYPE_RX_10G:
        break;
    default:
        return -EINVAL;
    }

    /* Find the pool */
    index = fman_port_find_bpool(port, bpid);
    if (index == port->ext_pools_num || index == FMAN_PORT_MAX_EXT_POOLS_NUM)
        /* Not found */
        return -EINVAL;

    tmp = ioread32be(&port->bmi_regs->rx.fmbm_ebmpi[index]);

    if (enable)
        tmp |= BMI_EXT_BUF_POOL_EN_COUNTER;
    else
        tmp &= ~BMI_EXT_BUF_POOL_EN_COUNTER;

    iowrite32be(tmp, &port->bmi_regs->rx.fmbm_ebmpi[index]);
    return 0;
}