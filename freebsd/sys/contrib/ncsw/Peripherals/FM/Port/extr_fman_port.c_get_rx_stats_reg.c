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
struct fman_port_rx_bmi_regs {int /*<<< orphan*/  fmbm_rfldec; int /*<<< orphan*/  fmbm_rffc; int /*<<< orphan*/  fmbm_rodc; int /*<<< orphan*/  fmbm_rlfc; int /*<<< orphan*/  fmbm_rfbc; int /*<<< orphan*/  fmbm_rbdc; int /*<<< orphan*/  fmbm_rfdc; int /*<<< orphan*/  fmbm_rfrc; } ;
struct fman_port {TYPE_1__* bmi_regs; } ;
typedef  enum fman_port_stats_counters { ____Placeholder_fman_port_stats_counters } fman_port_stats_counters ;
struct TYPE_2__ {struct fman_port_rx_bmi_regs rx; } ;

/* Variables and functions */
#define  E_FMAN_PORT_STATS_CNT_DEALLOC_BUF 135 
#define  E_FMAN_PORT_STATS_CNT_DISCARD 134 
#define  E_FMAN_PORT_STATS_CNT_DMA_ERR 133 
#define  E_FMAN_PORT_STATS_CNT_FILTERED_FRAME 132 
#define  E_FMAN_PORT_STATS_CNT_FRAME 131 
#define  E_FMAN_PORT_STATS_CNT_RX_BAD_FRAME 130 
#define  E_FMAN_PORT_STATS_CNT_RX_LARGE_FRAME 129 
#define  E_FMAN_PORT_STATS_CNT_RX_OUT_OF_BUF 128 

__attribute__((used)) static void get_rx_stats_reg(struct fman_port *port,
        enum fman_port_stats_counters counter,
        uint32_t **stats_reg)
{
    struct fman_port_rx_bmi_regs *regs = &port->bmi_regs->rx;

    switch (counter) {
    case E_FMAN_PORT_STATS_CNT_FRAME:
        *stats_reg = &regs->fmbm_rfrc;
        break;
    case E_FMAN_PORT_STATS_CNT_DISCARD:
        *stats_reg = &regs->fmbm_rfdc;
        break;
    case E_FMAN_PORT_STATS_CNT_DEALLOC_BUF:
        *stats_reg = &regs->fmbm_rbdc;
        break;
    case E_FMAN_PORT_STATS_CNT_RX_BAD_FRAME:
        *stats_reg = &regs->fmbm_rfbc;
        break;
    case E_FMAN_PORT_STATS_CNT_RX_LARGE_FRAME:
        *stats_reg = &regs->fmbm_rlfc;
        break;
    case E_FMAN_PORT_STATS_CNT_RX_OUT_OF_BUF:
        *stats_reg = &regs->fmbm_rodc;
        break;
    case E_FMAN_PORT_STATS_CNT_FILTERED_FRAME:
        *stats_reg = &regs->fmbm_rffc;
        break;
    case E_FMAN_PORT_STATS_CNT_DMA_ERR:
        *stats_reg = &regs->fmbm_rfldec;
        break;
    default:
        *stats_reg = NULL;
    }
}