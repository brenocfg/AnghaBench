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
 scalar_t__ check_TESTMechTypeList () ; 
 scalar_t__ check_fail_choice () ; 
 scalar_t__ check_fail_largetag () ; 
 scalar_t__ check_fail_sequence () ; 
 scalar_t__ check_seq () ; 
 scalar_t__ check_seq_of_size () ; 
 scalar_t__ check_tag_length () ; 
 scalar_t__ test_Name () ; 
 scalar_t__ test_authenticator () ; 
 scalar_t__ test_bit_string () ; 
 scalar_t__ test_bit_string_rfc1510 () ; 
 scalar_t__ test_cert () ; 
 scalar_t__ test_choice () ; 
 scalar_t__ test_implicit () ; 
 scalar_t__ test_krb_error () ; 
 scalar_t__ test_large_tag () ; 
 scalar_t__ test_optional () ; 
 scalar_t__ test_principal () ; 
 scalar_t__ test_taglessalloc () ; 
 scalar_t__ test_time () ; 

int
main(int argc, char **argv)
{
    int ret = 0;

    ret += test_principal ();
    ret += test_authenticator();
    ret += test_krb_error();
    ret += test_Name();
    ret += test_bit_string();
    ret += test_bit_string_rfc1510();
    ret += test_time();
    ret += test_cert();

    ret += check_tag_length();
    ret += test_large_tag();
    ret += test_choice();

    ret += test_implicit();
    ret += test_taglessalloc();
    ret += test_optional();

    ret += check_fail_largetag();
    ret += check_fail_sequence();
    ret += check_fail_choice();

    ret += check_seq();
    ret += check_seq_of_size();

    ret += check_TESTMechTypeList();

    return ret;
}