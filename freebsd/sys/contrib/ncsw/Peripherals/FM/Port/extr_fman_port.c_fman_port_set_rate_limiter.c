#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct fman_port_rate_limiter {int count_1micro_bit; int rate; int burst_size; int rate_factor; scalar_t__ high_burst_size_gran; } ;
struct fman_port {int type; int fm_rev_maj; TYPE_3__* bmi_regs; } ;
struct TYPE_5__ {int fmbm_orlmt; int fmbm_orlmts; } ;
struct TYPE_4__ {int fmbm_trlmt; int fmbm_trlmts; } ;
struct TYPE_6__ {TYPE_2__ oh; TYPE_1__ tx; } ;

/* Variables and functions */
 int BMI_RATE_LIMIT_GRAN_OP ; 
 int BMI_RATE_LIMIT_GRAN_TX ; 
 int BMI_RATE_LIMIT_HIGH_BURST_SIZE_GRAN ; 
 int BMI_RATE_LIMIT_MAX_BURST_SHIFT ; 
 int BMI_RATE_LIMIT_MAX_BURST_SIZE ; 
 int BMI_RATE_LIMIT_MAX_RATE_IN_GRAN_UNITS ; 
 int BMI_RATE_LIMIT_SCALE_EN ; 
 int BMI_RATE_LIMIT_SCALE_TSBS_SHIFT ; 
 int EINVAL ; 
#define  E_FMAN_PORT_TYPE_OP 130 
#define  E_FMAN_PORT_TYPE_TX 129 
#define  E_FMAN_PORT_TYPE_TX_10G 128 
 int /*<<< orphan*/  iowrite32be (int,int*) ; 

int fman_port_set_rate_limiter(struct fman_port *port,
        struct fman_port_rate_limiter *rate_limiter)
{
    uint32_t *rate_limit_reg, *rate_limit_scale_reg;
    uint32_t granularity, tmp;
    uint8_t usec_bit, factor;

    switch (port->type) {
    case E_FMAN_PORT_TYPE_TX:
    case E_FMAN_PORT_TYPE_TX_10G:
        rate_limit_reg = &port->bmi_regs->tx.fmbm_trlmt;
        rate_limit_scale_reg = &port->bmi_regs->tx.fmbm_trlmts;
        granularity = BMI_RATE_LIMIT_GRAN_TX;
        break;
    case E_FMAN_PORT_TYPE_OP:
        rate_limit_reg = &port->bmi_regs->oh.fmbm_orlmt;
        rate_limit_scale_reg = &port->bmi_regs->oh.fmbm_orlmts;
        granularity = BMI_RATE_LIMIT_GRAN_OP;
        break;
    default:
        return -EINVAL;
    }

    /* Factor is per 1 usec count */
    factor = 1;
    usec_bit = rate_limiter->count_1micro_bit;

    /* If rate limit is too small for an 1usec factor, adjust timestamp
     * scale and multiply the factor */
    while (rate_limiter->rate < (granularity / factor)) {
        if (usec_bit == 31)
            /* Can't configure rate limiter - rate is too small */
            return -EINVAL;

        usec_bit++;
        factor <<= 1;
    }

    /* Figure out register value. The "while" above quarantees that
     * (rate_limiter->rate * factor / granularity) >= 1 */
    tmp = (uint32_t)(rate_limiter->rate * factor / granularity - 1);

    /* Check rate limit isn't too large */
    if (tmp >= BMI_RATE_LIMIT_MAX_RATE_IN_GRAN_UNITS)
        return -EINVAL;

    /* Check burst size is in allowed range */
    if ((rate_limiter->burst_size == 0) ||
            (rate_limiter->burst_size >
                BMI_RATE_LIMIT_MAX_BURST_SIZE))
        return -EINVAL;

    tmp |= (uint32_t)(rate_limiter->burst_size - 1) <<
            BMI_RATE_LIMIT_MAX_BURST_SHIFT;

    if ((port->type == E_FMAN_PORT_TYPE_OP) &&
            (port->fm_rev_maj == 4)) {
        if (rate_limiter->high_burst_size_gran)
            tmp |= BMI_RATE_LIMIT_HIGH_BURST_SIZE_GRAN;
    }

    iowrite32be(tmp, rate_limit_reg);

    /* Set up rate limiter scale register */
    tmp = BMI_RATE_LIMIT_SCALE_EN;
    tmp |= (31 - (uint32_t)usec_bit) << BMI_RATE_LIMIT_SCALE_TSBS_SHIFT;

    if ((port->type == E_FMAN_PORT_TYPE_OP) &&
            (port->fm_rev_maj == 4))
        tmp |= rate_limiter->rate_factor;

    iowrite32be(tmp, rate_limit_scale_reg);

    return 0;
}