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
struct TYPE_6__ {int tx_oe; } ;
struct TYPE_7__ {void* u64; TYPE_2__ s; } ;
typedef  TYPE_3__ cvmx_gpio_xbit_cfgx_t ;
struct TYPE_5__ {int tx_oe; } ;
struct TYPE_8__ {void* u64; TYPE_1__ s; } ;
typedef  TYPE_4__ cvmx_gpio_bit_cfgx_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_GPIO_BIT_CFGX (int) ; 
 int /*<<< orphan*/  CVMX_GPIO_XBIT_CFGX (int) ; 
 int /*<<< orphan*/  OCTEON_CN61XX ; 
 int /*<<< orphan*/  OCTEON_CN66XX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,int) ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static inline void cvmx_gpio_cfg(int bit, int mode)
{
    if (bit > 15 && bit < 20)
    {
        /* CN61XX/CN66XX has 20 GPIO pins and only 16 are interruptable. */
        if (OCTEON_IS_MODEL(OCTEON_CN61XX) || OCTEON_IS_MODEL(OCTEON_CN66XX))
        {
            cvmx_gpio_xbit_cfgx_t gpio_xbit;
            gpio_xbit.u64 = cvmx_read_csr(CVMX_GPIO_XBIT_CFGX(bit));
            if (mode)
                gpio_xbit.s.tx_oe = 1;
            else
                gpio_xbit.s.tx_oe = 0;
            cvmx_write_csr(CVMX_GPIO_XBIT_CFGX(bit), gpio_xbit.u64);
        }
        else
            cvmx_dprintf("cvmx_gpio_cfg: Invalid GPIO bit(%d)\n", bit);
    }
    else
    {
        cvmx_gpio_bit_cfgx_t gpio_bit;
        gpio_bit.u64 = cvmx_read_csr(CVMX_GPIO_BIT_CFGX(bit));
        if (mode)
            gpio_bit.s.tx_oe = 1;
        else
            gpio_bit.s.tx_oe = 0;
        cvmx_write_csr(CVMX_GPIO_BIT_CFGX(bit), gpio_bit.u64);
    }
}