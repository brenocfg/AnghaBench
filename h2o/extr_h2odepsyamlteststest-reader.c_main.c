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
 int check_boms () ; 
 int check_long_utf16 () ; 
 int check_long_utf8 () ; 
 int check_utf8_sequences () ; 

int
main(void)
{
    return check_utf8_sequences() + check_boms() + check_long_utf8() + check_long_utf16();
}