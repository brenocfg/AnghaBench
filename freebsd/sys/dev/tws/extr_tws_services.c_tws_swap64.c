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
typedef  int u_int64_t ;
typedef  int u_int32_t ;

/* Variables and functions */
 scalar_t__ tws_swap32 (int) ; 

u_int64_t 
tws_swap64(u_int64_t val)
{
    return((((u_int64_t)(tws_swap32(((u_int32_t *)(&(val)))[1]))) << 32) |
           ((u_int32_t)(tws_swap32(((u_int32_t *)(&(val)))[0]))));
}