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
typedef  union q_util {int dummy; } q_util ;
typedef  union l_util {int dummy; } l_util ;
typedef  scalar_t__ u_short ;
typedef  scalar_t__ u_int64_t ;
typedef  scalar_t__ u_int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  REDUCE16 ; 

u_short
in_pseudo(u_int32_t a, u_int32_t b, u_int32_t c)
{
	u_int64_t sum;
	union q_util q_util;
	union l_util l_util;
		    
	sum = (u_int64_t) a + b + c;
	REDUCE16;
	return (sum);
}