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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {int start_bit; int stop_bit; } ;
typedef  TYPE_1__ __cvmx_qlm_jtag_field_t ;

/* Variables and functions */
 TYPE_1__* __cvmx_qlm_lookup_field (char const*) ; 
 int /*<<< orphan*/  cvmx_helper_qlm_jtag_capture (int) ; 
 int /*<<< orphan*/  cvmx_helper_qlm_jtag_shift (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_helper_qlm_jtag_shift_zeros (int,int) ; 
 int cvmx_qlm_get_lanes (int) ; 
 int cvmx_qlm_jtag_get_length () ; 

uint64_t cvmx_qlm_jtag_get(int qlm, int lane, const char *name)
{
    const __cvmx_qlm_jtag_field_t *field = __cvmx_qlm_lookup_field(name);
    int qlm_jtag_length = cvmx_qlm_jtag_get_length();
    int num_lanes = cvmx_qlm_get_lanes(qlm);

    if (!field)
        return 0;

    /* Capture the current settings */
    cvmx_helper_qlm_jtag_capture(qlm);
    /* Shift past lanes we don't care about. CN6XXX shifts lane 3 first */
    cvmx_helper_qlm_jtag_shift_zeros(qlm, qlm_jtag_length * (num_lanes-1-lane));    /* Shift to the start of the field */
    cvmx_helper_qlm_jtag_shift_zeros(qlm, field->start_bit);
    /* Shift out the value and return it */
    return cvmx_helper_qlm_jtag_shift(qlm, field->stop_bit - field->start_bit + 1, 0);
}