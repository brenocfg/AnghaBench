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
typedef  int uint32_t ;
struct fman_port {size_t ext_pools_num; TYPE_2__* bmi_regs; } ;
struct TYPE_3__ {int* fmbm_ebmpi; } ;
struct TYPE_4__ {TYPE_1__ rx; } ;

/* Variables and functions */
 int BMI_EXT_BUF_POOL_ID_MASK ; 
 int BMI_EXT_BUF_POOL_ID_SHIFT ; 
 size_t FMAN_PORT_MAX_EXT_POOLS_NUM ; 
 int ioread32be (int*) ; 

__attribute__((used)) static uint8_t fman_port_find_bpool(struct fman_port *port, uint8_t bpid)
{
    uint32_t *bp_reg, tmp;
    uint8_t i, id;

    /* Find the pool */
    bp_reg = port->bmi_regs->rx.fmbm_ebmpi;
    for (i = 0;
         (i < port->ext_pools_num && (i < FMAN_PORT_MAX_EXT_POOLS_NUM));
         i++) {
        tmp = ioread32be(&bp_reg[i]);
        id = (uint8_t)((tmp & BMI_EXT_BUF_POOL_ID_MASK) >>
                BMI_EXT_BUF_POOL_ID_SHIFT);

        if (id == bpid)
            break;
    }

    return i;
}