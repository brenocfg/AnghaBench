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
typedef  int /*<<< orphan*/  uint32_t ;
struct fman_port {TYPE_1__* qmi_regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  fmqm_pnc; } ;

/* Variables and functions */
 int /*<<< orphan*/  QMI_PORT_CFG_EN_COUNTERS ; 
 int /*<<< orphan*/  ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int fman_port_set_queue_cnt_mode(struct fman_port *port, bool enable)
{
    uint32_t tmp;

    tmp = ioread32be(&port->qmi_regs->fmqm_pnc);

    if (enable)
        tmp |= QMI_PORT_CFG_EN_COUNTERS;
    else
        tmp &= ~QMI_PORT_CFG_EN_COUNTERS;

    iowrite32be(tmp, &port->qmi_regs->fmqm_pnc);
    return 0;
}