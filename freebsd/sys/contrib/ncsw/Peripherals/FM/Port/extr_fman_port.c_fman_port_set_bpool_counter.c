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
struct TYPE_3__ {int /*<<< orphan*/ * fmbm_acnt; } ;
struct TYPE_4__ {TYPE_1__ rx; } ;

/* Variables and functions */
#define  E_FMAN_PORT_TYPE_RX 129 
#define  E_FMAN_PORT_TYPE_RX_10G 128 
 size_t FMAN_PORT_MAX_EXT_POOLS_NUM ; 
 size_t fman_port_find_bpool (struct fman_port*,size_t) ; 
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void fman_port_set_bpool_counter(struct fman_port *port,
        uint8_t bpid,
        uint32_t value)
{
    uint8_t index;

    switch (port->type) {
    case E_FMAN_PORT_TYPE_RX:
    case E_FMAN_PORT_TYPE_RX_10G:
        break;
    default:
        return;
    }

    /* Find the pool */
    index = fman_port_find_bpool(port, bpid);
    if (index == port->ext_pools_num || index == FMAN_PORT_MAX_EXT_POOLS_NUM)
        /* Not found */
        return;

    iowrite32be(value, &port->bmi_regs->rx.fmbm_acnt[index]);
}