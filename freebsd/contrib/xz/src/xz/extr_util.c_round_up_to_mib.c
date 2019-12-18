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
typedef  int uint64_t ;

/* Variables and functions */
 int UINT32_C (int) ; 

extern uint64_t
round_up_to_mib(uint64_t n)
{
	return (n >> 20) + ((n & ((UINT32_C(1) << 20) - 1)) != 0);
}