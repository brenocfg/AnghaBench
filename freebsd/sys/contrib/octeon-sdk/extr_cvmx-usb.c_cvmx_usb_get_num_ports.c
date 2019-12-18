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

/* Variables and functions */
 int /*<<< orphan*/  OCTEON_CN30XX ; 
 int /*<<< orphan*/  OCTEON_CN31XX ; 
 int /*<<< orphan*/  OCTEON_CN50XX ; 
 int /*<<< orphan*/  OCTEON_CN52XX ; 
 int /*<<< orphan*/  OCTEON_CN56XX ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int __cvmx_helper_board_usb_get_num_ports (int) ; 

int cvmx_usb_get_num_ports(void)
{
    int arch_ports = 0;

    if (OCTEON_IS_MODEL(OCTEON_CN56XX))
        arch_ports = 1;
    else if (OCTEON_IS_MODEL(OCTEON_CN52XX))
        arch_ports = 2;
    else if (OCTEON_IS_MODEL(OCTEON_CN50XX))
        arch_ports = 1;
    else if (OCTEON_IS_MODEL(OCTEON_CN31XX))
        arch_ports = 1;
    else if (OCTEON_IS_MODEL(OCTEON_CN30XX))
        arch_ports = 1;
    else
        arch_ports = 0;

    return __cvmx_helper_board_usb_get_num_ports(arch_ports);
}