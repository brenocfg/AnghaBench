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
struct fman_port_oh_bmi_regs {int /*<<< orphan*/  fmbm_ofwdc; int /*<<< orphan*/  fmbm_ofufdc; int /*<<< orphan*/  fmbm_ofledc; int /*<<< orphan*/  fmbm_ofldec; int /*<<< orphan*/  fmbm_offc; int /*<<< orphan*/  fmbm_obdc; int /*<<< orphan*/  fmbm_ofdc; int /*<<< orphan*/  fmbm_ofrc; } ;
struct fman_port {TYPE_1__* bmi_regs; } ;
typedef  enum fman_port_stats_counters { ____Placeholder_fman_port_stats_counters } fman_port_stats_counters ;
struct TYPE_2__ {struct fman_port_oh_bmi_regs oh; } ;

/* Variables and functions */
#define  E_FMAN_PORT_STATS_CNT_DEALLOC_BUF 135 
#define  E_FMAN_PORT_STATS_CNT_DISCARD 134 
#define  E_FMAN_PORT_STATS_CNT_DMA_ERR 133 
#define  E_FMAN_PORT_STATS_CNT_FILTERED_FRAME 132 
#define  E_FMAN_PORT_STATS_CNT_FRAME 131 
#define  E_FMAN_PORT_STATS_CNT_LEN_ERR 130 
#define  E_FMAN_PORT_STATS_CNT_UNSUPPORTED_FORMAT 129 
#define  E_FMAN_PORT_STATS_CNT_WRED_DISCARD 128 

__attribute__((used)) static void get_oh_stats_reg(struct fman_port *port,
        enum fman_port_stats_counters counter,
        uint32_t **stats_reg)
{
    struct fman_port_oh_bmi_regs *regs = &port->bmi_regs->oh;

    switch (counter) {
    case E_FMAN_PORT_STATS_CNT_FRAME:
        *stats_reg = &regs->fmbm_ofrc;
        break;
    case E_FMAN_PORT_STATS_CNT_DISCARD:
        *stats_reg = &regs->fmbm_ofdc;
        break;
    case E_FMAN_PORT_STATS_CNT_DEALLOC_BUF:
        *stats_reg = &regs->fmbm_obdc;
        break;
    case E_FMAN_PORT_STATS_CNT_FILTERED_FRAME:
        *stats_reg = &regs->fmbm_offc;
        break;
    case E_FMAN_PORT_STATS_CNT_DMA_ERR:
        *stats_reg = &regs->fmbm_ofldec;
        break;
    case E_FMAN_PORT_STATS_CNT_LEN_ERR:
        *stats_reg = &regs->fmbm_ofledc;
        break;
    case E_FMAN_PORT_STATS_CNT_UNSUPPORTED_FORMAT:
        *stats_reg = &regs->fmbm_ofufdc;
        break;
    case E_FMAN_PORT_STATS_CNT_WRED_DISCARD:
        *stats_reg = &regs->fmbm_ofwdc;
        break;
    default:
        *stats_reg = NULL;
    }
}