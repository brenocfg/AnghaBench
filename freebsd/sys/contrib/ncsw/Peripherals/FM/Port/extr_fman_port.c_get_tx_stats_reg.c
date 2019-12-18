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
struct fman_port_tx_bmi_regs {int /*<<< orphan*/  fmbm_tfufdc; int /*<<< orphan*/  fmbm_tfledc; int /*<<< orphan*/  fmbm_tbdc; int /*<<< orphan*/  fmbm_tfdc; int /*<<< orphan*/  fmbm_tfrc; } ;
struct fman_port {TYPE_1__* bmi_regs; } ;
typedef  enum fman_port_stats_counters { ____Placeholder_fman_port_stats_counters } fman_port_stats_counters ;
struct TYPE_2__ {struct fman_port_tx_bmi_regs tx; } ;

/* Variables and functions */
#define  E_FMAN_PORT_STATS_CNT_DEALLOC_BUF 132 
#define  E_FMAN_PORT_STATS_CNT_DISCARD 131 
#define  E_FMAN_PORT_STATS_CNT_FRAME 130 
#define  E_FMAN_PORT_STATS_CNT_LEN_ERR 129 
#define  E_FMAN_PORT_STATS_CNT_UNSUPPORTED_FORMAT 128 

__attribute__((used)) static void get_tx_stats_reg(struct fman_port *port,
        enum fman_port_stats_counters counter,
        uint32_t **stats_reg)
{
    struct fman_port_tx_bmi_regs *regs = &port->bmi_regs->tx;

    switch (counter) {
    case E_FMAN_PORT_STATS_CNT_FRAME:
        *stats_reg = &regs->fmbm_tfrc;
        break;
    case E_FMAN_PORT_STATS_CNT_DISCARD:
        *stats_reg = &regs->fmbm_tfdc;
        break;
    case E_FMAN_PORT_STATS_CNT_DEALLOC_BUF:
        *stats_reg = &regs->fmbm_tbdc;
        break;
    case E_FMAN_PORT_STATS_CNT_LEN_ERR:
        *stats_reg = &regs->fmbm_tfledc;
        break;
    case E_FMAN_PORT_STATS_CNT_UNSUPPORTED_FORMAT:
        *stats_reg = &regs->fmbm_tfufdc;
        break;
    default:
        *stats_reg = NULL;
    }
}