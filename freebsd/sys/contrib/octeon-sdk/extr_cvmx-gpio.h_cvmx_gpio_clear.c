#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  clr; } ;
struct TYPE_4__ {scalar_t__ u64; TYPE_1__ s; } ;
typedef  TYPE_2__ cvmx_gpio_tx_clr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_GPIO_TX_CLR ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void cvmx_gpio_clear(uint32_t clear_mask)
{
    cvmx_gpio_tx_clr_t gpio_tx_clr;
    gpio_tx_clr.u64 = 0;
    gpio_tx_clr.s.clr = clear_mask;
    cvmx_write_csr(CVMX_GPIO_TX_CLR, gpio_tx_clr.u64);
}