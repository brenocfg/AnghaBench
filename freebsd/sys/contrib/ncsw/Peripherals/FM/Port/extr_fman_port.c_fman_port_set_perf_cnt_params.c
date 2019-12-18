#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct fman_port_perf_cnt_params {int task_val; int dma_val; int fifo_val; int /*<<< orphan*/  queue_val; } ;
struct fman_port {int type; TYPE_4__* bmi_regs; } ;
struct TYPE_7__ {int fmbm_opcp; } ;
struct TYPE_6__ {int fmbm_tpcp; } ;
struct TYPE_5__ {int fmbm_rpcp; } ;
struct TYPE_8__ {TYPE_3__ oh; TYPE_2__ tx; TYPE_1__ rx; } ;

/* Variables and functions */
 int BMI_PERFORMANCE_DMA_COMP_SHIFT ; 
 int BMI_PERFORMANCE_QUEUE_COMP_SHIFT ; 
 int BMI_PERFORMANCE_TASK_COMP_SHIFT ; 
 int EINVAL ; 
#define  E_FMAN_PORT_TYPE_HC 133 
#define  E_FMAN_PORT_TYPE_OP 132 
#define  E_FMAN_PORT_TYPE_RX 131 
#define  E_FMAN_PORT_TYPE_RX_10G 130 
#define  E_FMAN_PORT_TYPE_TX 129 
#define  E_FMAN_PORT_TYPE_TX_10G 128 
 int FMAN_PORT_BMI_FIFO_UNITS ; 
 int MAX_PERFORMANCE_DMA_COMP ; 
 int MAX_PERFORMANCE_FIFO_COMP ; 
 int /*<<< orphan*/  MAX_PERFORMANCE_RX_QUEUE_COMP ; 
 int MAX_PERFORMANCE_TASK_COMP ; 
 int /*<<< orphan*/  MAX_PERFORMANCE_TX_QUEUE_COMP ; 
 int /*<<< orphan*/  iowrite32be (int,int*) ; 

int fman_port_set_perf_cnt_params(struct fman_port *port,
        struct fman_port_perf_cnt_params *params)
{
    uint32_t *pcp_reg, tmp;

    /* Obtain register address and check parameters are in range */
    switch (port->type) {
    case E_FMAN_PORT_TYPE_RX:
    case E_FMAN_PORT_TYPE_RX_10G:
        pcp_reg = &port->bmi_regs->rx.fmbm_rpcp;
        if ((params->queue_val == 0) ||
            (params->queue_val > MAX_PERFORMANCE_RX_QUEUE_COMP))
            return -EINVAL;
        break;
    case E_FMAN_PORT_TYPE_TX:
    case E_FMAN_PORT_TYPE_TX_10G:
        pcp_reg = &port->bmi_regs->tx.fmbm_tpcp;
        if ((params->queue_val == 0) ||
            (params->queue_val > MAX_PERFORMANCE_TX_QUEUE_COMP))
            return -EINVAL;
        break;
    case E_FMAN_PORT_TYPE_OP:
    case E_FMAN_PORT_TYPE_HC:
        pcp_reg = &port->bmi_regs->oh.fmbm_opcp;
        if (params->queue_val != 0)
            return -EINVAL;
        break;
    default:
        return -EINVAL;
    }

    if ((params->task_val == 0) ||
            (params->task_val > MAX_PERFORMANCE_TASK_COMP))
        return -EINVAL;
    if ((params->dma_val == 0) ||
            (params->dma_val > MAX_PERFORMANCE_DMA_COMP))
        return -EINVAL;
    if ((params->fifo_val == 0) ||
            ((params->fifo_val / FMAN_PORT_BMI_FIFO_UNITS) >
                MAX_PERFORMANCE_FIFO_COMP))
        return -EINVAL;
    tmp = (uint32_t)(params->task_val - 1) <<
            BMI_PERFORMANCE_TASK_COMP_SHIFT;
    tmp |= (uint32_t)(params->dma_val - 1) <<
            BMI_PERFORMANCE_DMA_COMP_SHIFT;
    tmp |= (uint32_t)(params->fifo_val / FMAN_PORT_BMI_FIFO_UNITS - 1);

    switch (port->type) {
    case E_FMAN_PORT_TYPE_RX:
    case E_FMAN_PORT_TYPE_RX_10G:
    case E_FMAN_PORT_TYPE_TX:
    case E_FMAN_PORT_TYPE_TX_10G:
        tmp |= (uint32_t)(params->queue_val - 1) <<
            BMI_PERFORMANCE_QUEUE_COMP_SHIFT;
        break;
    default:
        break;
    }


    iowrite32be(tmp, pcp_reg);
    return 0;
}