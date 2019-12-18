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
struct fman_port_tx_bmi_regs {int /*<<< orphan*/  fmbm_tfuc; int /*<<< orphan*/  fmbm_tduc; int /*<<< orphan*/  fmbm_ttcquc; int /*<<< orphan*/  fmbm_ttuc; int /*<<< orphan*/  fmbm_tccn; } ;
struct fman_port {TYPE_1__* bmi_regs; } ;
typedef  enum fman_port_perf_counters { ____Placeholder_fman_port_perf_counters } fman_port_perf_counters ;
struct TYPE_2__ {struct fman_port_tx_bmi_regs tx; } ;

/* Variables and functions */
#define  E_FMAN_PORT_PERF_CNT_CYCLE 132 
#define  E_FMAN_PORT_PERF_CNT_DMA_UTIL 131 
#define  E_FMAN_PORT_PERF_CNT_FIFO_UTIL 130 
#define  E_FMAN_PORT_PERF_CNT_QUEUE_UTIL 129 
#define  E_FMAN_PORT_PERF_CNT_TASK_UTIL 128 

__attribute__((used)) static void get_tx_perf_reg(struct fman_port *port,
        enum fman_port_perf_counters counter,
        uint32_t **perf_reg)
{
    struct fman_port_tx_bmi_regs *regs = &port->bmi_regs->tx;

    switch (counter) {
    case E_FMAN_PORT_PERF_CNT_CYCLE:
        *perf_reg = &regs->fmbm_tccn;
        break;
    case E_FMAN_PORT_PERF_CNT_TASK_UTIL:
        *perf_reg = &regs->fmbm_ttuc;
        break;
    case E_FMAN_PORT_PERF_CNT_QUEUE_UTIL:
        *perf_reg = &regs->fmbm_ttcquc;
        break;
    case E_FMAN_PORT_PERF_CNT_DMA_UTIL:
        *perf_reg = &regs->fmbm_tduc;
        break;
    case E_FMAN_PORT_PERF_CNT_FIFO_UTIL:
        *perf_reg = &regs->fmbm_tfuc;
        break;
    default:
        *perf_reg = NULL;
    }
}