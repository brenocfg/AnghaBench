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
struct fman_port {int type; } ;
typedef  enum fman_port_perf_counters { ____Placeholder_fman_port_perf_counters } fman_port_perf_counters ;

/* Variables and functions */
#define  E_FMAN_PORT_TYPE_HC 133 
#define  E_FMAN_PORT_TYPE_OP 132 
#define  E_FMAN_PORT_TYPE_RX 131 
#define  E_FMAN_PORT_TYPE_RX_10G 130 
#define  E_FMAN_PORT_TYPE_TX 129 
#define  E_FMAN_PORT_TYPE_TX_10G 128 
 int /*<<< orphan*/  get_oh_perf_reg (struct fman_port*,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  get_rx_perf_reg (struct fman_port*,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  get_tx_perf_reg (struct fman_port*,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void fman_port_set_perf_counter(struct fman_port *port,
        enum fman_port_perf_counters counter,
        uint32_t value)
{
    uint32_t *perf_reg;

    switch (port->type) {
    case E_FMAN_PORT_TYPE_RX:
    case E_FMAN_PORT_TYPE_RX_10G:
        get_rx_perf_reg(port, counter, &perf_reg);
        break;
    case E_FMAN_PORT_TYPE_TX:
    case E_FMAN_PORT_TYPE_TX_10G:
        get_tx_perf_reg(port, counter, &perf_reg);
        break;
    case E_FMAN_PORT_TYPE_OP:
    case E_FMAN_PORT_TYPE_HC:
        get_oh_perf_reg(port, counter, &perf_reg);
        break;
    default:
        perf_reg = NULL;
    }

    if (perf_reg == NULL)
        return;

    iowrite32be(value, perf_reg);
}