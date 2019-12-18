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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct fman_port {int type; TYPE_1__* bmi_regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  fmbm_rfne; } ;
struct TYPE_3__ {TYPE_2__ rx; } ;

/* Variables and functions */
 int BMI_NEXT_ENG_FD_BITS_SHIFT ; 
 int EINVAL ; 
#define  E_FMAN_PORT_TYPE_RX 129 
#define  E_FMAN_PORT_TYPE_RX_10G 128 
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 

int fman_port_modify_rx_fd_bits(struct fman_port *port,
        uint8_t rx_fd_bits,
        bool add)
{
    uint32_t    tmp;

    switch (port->type) {
    case E_FMAN_PORT_TYPE_RX:
    case E_FMAN_PORT_TYPE_RX_10G:
        break;
    default:
        return -EINVAL;
    }

    tmp = ioread32be(&port->bmi_regs->rx.fmbm_rfne);

    if (add)
        tmp |= (uint32_t)rx_fd_bits << BMI_NEXT_ENG_FD_BITS_SHIFT;
    else
        tmp &= ~((uint32_t)rx_fd_bits << BMI_NEXT_ENG_FD_BITS_SHIFT);

    iowrite32be(tmp, &port->bmi_regs->rx.fmbm_rfne);
    return 0;
}