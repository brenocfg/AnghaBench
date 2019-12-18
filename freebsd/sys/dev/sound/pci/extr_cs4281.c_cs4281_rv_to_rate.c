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
typedef  size_t u_int8_t ;
typedef  int u_int32_t ;

/* Variables and functions */
 size_t CS4281_NUM_RATES ; 
 int* cs4281_rates ; 

__attribute__((used)) static u_int32_t
cs4281_rv_to_rate(u_int8_t rv)
{
    u_int32_t r;

    if (rv < CS4281_NUM_RATES) return cs4281_rates[rv];
    r = 1536000 / rv;
    return r;
}