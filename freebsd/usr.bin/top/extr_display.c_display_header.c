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
 scalar_t__ ERASE ; 
 scalar_t__ ON ; 
 scalar_t__ header_status ; 

void
display_header(int t)
{

    if (t)
    {
	header_status = ON;
    }
    else if (header_status == ON)
    {
	header_status = ERASE;
    }
}