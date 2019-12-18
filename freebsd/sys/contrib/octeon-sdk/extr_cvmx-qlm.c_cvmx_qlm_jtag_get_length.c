#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int stop_bit; scalar_t__ name; } ;
typedef  TYPE_1__ __cvmx_qlm_jtag_field_t ;

/* Variables and functions */
 TYPE_1__* cvmx_qlm_jtag_get_field () ; 

int cvmx_qlm_jtag_get_length(void)
{
    const __cvmx_qlm_jtag_field_t *qlm_ptr = cvmx_qlm_jtag_get_field();
    int length = 0;

    /* Figure out how many bits are in the JTAG chain */
    while (qlm_ptr != NULL && qlm_ptr->name)
    {
        if (qlm_ptr->stop_bit > length)
            length = qlm_ptr->stop_bit + 1;
        qlm_ptr++;
    }
    return length;
}