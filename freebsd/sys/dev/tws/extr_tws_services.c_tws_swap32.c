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
typedef  int u_int32_t ;

/* Variables and functions */

u_int32_t 
tws_swap32(u_int32_t val)
{
    return(((val << 24) | ((val << 8) & (0xFF0000)) | 
           ((val >> 8) & (0xFF00)) | (val >> 24)));
}