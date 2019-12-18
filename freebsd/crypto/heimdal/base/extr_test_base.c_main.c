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
 int test_auto_release () ; 
 int test_dict () ; 
 int test_memory () ; 
 int test_string () ; 

int
main(int argc, char **argv)
{
    int res = 0;

    res |= test_memory();
    res |= test_dict();
    res |= test_auto_release();
    res |= test_string();

    return res;
}