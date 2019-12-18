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
 scalar_t__ check_fail_bitstring () ; 
 scalar_t__ check_fail_bmp_string () ; 
 scalar_t__ check_fail_boolean () ; 
 scalar_t__ check_fail_general_string () ; 
 scalar_t__ check_fail_generalized_time () ; 
 scalar_t__ check_fail_heim_integer () ; 
 scalar_t__ check_fail_integer () ; 
 scalar_t__ check_fail_length () ; 
 scalar_t__ check_fail_oid () ; 
 scalar_t__ check_fail_universal_string () ; 
 scalar_t__ check_fail_unsigned () ; 
 scalar_t__ check_trailing_nul () ; 
 scalar_t__ corner_generalized_time () ; 
 scalar_t__ corner_tag () ; 
 scalar_t__ test_bit_string () ; 
 scalar_t__ test_bmp_string () ; 
 scalar_t__ test_boolean () ; 
 scalar_t__ test_general_string () ; 
 scalar_t__ test_generalized_time () ; 
 scalar_t__ test_heim_int_format () ; 
 scalar_t__ test_heim_integer () ; 
 scalar_t__ test_heim_oid_format () ; 
 scalar_t__ test_integer () ; 
 scalar_t__ test_integer_more () ; 
 scalar_t__ test_misc_cmp () ; 
 scalar_t__ test_octet_string () ; 
 scalar_t__ test_oid () ; 
 scalar_t__ test_universal_string () ; 
 scalar_t__ test_unsigned () ; 

int
main(int argc, char **argv)
{
    int ret = 0;

    ret += test_integer ();
    ret += test_integer_more();
    ret += test_unsigned ();
    ret += test_octet_string ();
    ret += test_bmp_string ();
    ret += test_universal_string ();
    ret += test_general_string ();
    ret += test_generalized_time ();
    ret += test_oid ();
    ret += test_bit_string();
    ret += test_heim_integer();
    ret += test_boolean();

    ret += check_fail_unsigned();
    ret += check_fail_integer();
    ret += check_fail_length();
    ret += check_fail_boolean();
    ret += check_fail_general_string();
    ret += check_fail_bmp_string();
    ret += check_fail_universal_string();
    ret += check_fail_heim_integer();
    ret += check_fail_generalized_time();
    ret += check_fail_oid();
    ret += check_fail_bitstring();
    ret += test_heim_int_format();
    ret += test_heim_oid_format();
    ret += check_trailing_nul();
    ret += test_misc_cmp();
    ret += corner_generalized_time();
    ret += corner_tag();

    return ret;
}