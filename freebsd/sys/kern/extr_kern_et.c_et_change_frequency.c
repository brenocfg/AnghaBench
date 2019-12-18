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
typedef  int /*<<< orphan*/  uint64_t ;
struct eventtimer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_et_frequency (struct eventtimer*,int /*<<< orphan*/ ) ; 

void
et_change_frequency(struct eventtimer *et, uint64_t newfreq)
{

#ifndef NO_EVENTTIMERS
	cpu_et_frequency(et, newfreq);
#endif
}