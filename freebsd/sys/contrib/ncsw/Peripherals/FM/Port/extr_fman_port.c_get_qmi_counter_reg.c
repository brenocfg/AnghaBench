#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct fman_port_qmi_regs {int /*<<< orphan*/  fmqm_pndcc; int /*<<< orphan*/  fmqm_pndfdc; int /*<<< orphan*/  fmqm_pndtfc; int /*<<< orphan*/  fmqm_pnetfc; } ;
struct fman_port {int /*<<< orphan*/  type; struct fman_port_qmi_regs* qmi_regs; } ;
typedef  enum fman_port_qmi_counters { ____Placeholder_fman_port_qmi_counters } fman_port_qmi_counters ;

/* Variables and functions */
#define  E_FMAN_PORT_DEQ_CONFIRM 131 
#define  E_FMAN_PORT_DEQ_FROM_DFLT 130 
#define  E_FMAN_PORT_DEQ_TOTAL 129 
#define  E_FMAN_PORT_ENQ_TOTAL 128 
 int /*<<< orphan*/  E_FMAN_PORT_TYPE_RX ; 
 int /*<<< orphan*/  E_FMAN_PORT_TYPE_RX_10G ; 

__attribute__((used)) static void get_qmi_counter_reg(struct fman_port *port,
        enum fman_port_qmi_counters  counter,
        uint32_t **queue_reg)
{
    struct fman_port_qmi_regs *regs = port->qmi_regs;

    switch (counter) {
    case E_FMAN_PORT_ENQ_TOTAL:
        *queue_reg = &regs->fmqm_pnetfc;
        break;
    case E_FMAN_PORT_DEQ_TOTAL:
        if ((port->type == E_FMAN_PORT_TYPE_RX) ||
                (port->type == E_FMAN_PORT_TYPE_RX_10G))
            /* Counter not available for Rx ports */
            *queue_reg = NULL;
        else
            *queue_reg = &regs->fmqm_pndtfc;
        break;
    case E_FMAN_PORT_DEQ_FROM_DFLT:
        if ((port->type == E_FMAN_PORT_TYPE_RX) ||
                (port->type == E_FMAN_PORT_TYPE_RX_10G))
            /* Counter not available for Rx ports */
            *queue_reg = NULL;
        else
            *queue_reg = &regs->fmqm_pndfdc;
        break;
    case E_FMAN_PORT_DEQ_CONFIRM:
        if ((port->type == E_FMAN_PORT_TYPE_RX) ||
                (port->type == E_FMAN_PORT_TYPE_RX_10G))
            /* Counter not available for Rx ports */
            *queue_reg = NULL;
        else
            *queue_reg = &regs->fmqm_pndcc;
        break;
    default:
        *queue_reg = NULL;
    }
}