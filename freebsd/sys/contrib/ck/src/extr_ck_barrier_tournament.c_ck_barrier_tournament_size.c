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
 unsigned int ck_internal_log (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ck_internal_power_2 (unsigned int) ; 

unsigned int
ck_barrier_tournament_size(unsigned int nthr)
{

	return (ck_internal_log(ck_internal_power_2(nthr)) + 1);
}