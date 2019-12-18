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
typedef  scalar_t__ HPT_U32 ;

/* Variables and functions */
 scalar_t__ random () ; 

HPT_U32 os_get_stamp(void)
{
    HPT_U32 stamp;
    do { stamp = random(); } while (stamp==0);
    return stamp;
}