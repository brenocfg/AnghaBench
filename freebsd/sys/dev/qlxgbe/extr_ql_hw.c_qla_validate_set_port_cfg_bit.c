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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static int
qla_validate_set_port_cfg_bit(uint32_t bits)
{
        if ((bits & 0xF) > 1)
                return (-1);

        if (((bits >> 4) & 0xF) > 2)
                return (-1);

        if (((bits >> 8) & 0xF) > 2)
                return (-1);

        return (0);
}