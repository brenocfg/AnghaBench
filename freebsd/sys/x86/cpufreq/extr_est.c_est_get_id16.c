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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_PERF_STATUS ; 
 int rdmsr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
est_get_id16(uint16_t *id16_p)
{
	*id16_p = rdmsr(MSR_PERF_STATUS) & 0xffff;
}