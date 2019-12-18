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
typedef  enum fman_port_stats_counters { ____Placeholder_fman_port_stats_counters } fman_port_stats_counters ;

/* Variables and functions */
#define  E_FMAN_PORT_TYPE_HC 133 
#define  E_FMAN_PORT_TYPE_OP 132 
#define  E_FMAN_PORT_TYPE_RX 131 
#define  E_FMAN_PORT_TYPE_RX_10G 130 
#define  E_FMAN_PORT_TYPE_TX 129 
#define  E_FMAN_PORT_TYPE_TX_10G 128 
 int /*<<< orphan*/  get_oh_stats_reg (struct fman_port*,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  get_rx_stats_reg (struct fman_port*,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  get_tx_stats_reg (struct fman_port*,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ioread32be (int /*<<< orphan*/ *) ; 

uint32_t fman_port_get_stats_counter(struct fman_port *port,
        enum fman_port_stats_counters  counter)
{
    uint32_t *stats_reg, ret_val;

    switch (port->type) {
    case E_FMAN_PORT_TYPE_RX:
    case E_FMAN_PORT_TYPE_RX_10G:
        get_rx_stats_reg(port, counter, &stats_reg);
        break;
    case E_FMAN_PORT_TYPE_TX:
    case E_FMAN_PORT_TYPE_TX_10G:
        get_tx_stats_reg(port, counter, &stats_reg);
        break;
    case E_FMAN_PORT_TYPE_OP:
    case E_FMAN_PORT_TYPE_HC:
        get_oh_stats_reg(port, counter, &stats_reg);
        break;
    default:
        stats_reg = NULL;
    }

    if (stats_reg == NULL)
        return 0;

    ret_val = ioread32be(stats_reg);
    return ret_val;
}