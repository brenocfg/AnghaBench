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
typedef  void* uint64_t ;
struct eventtimer {void* et_frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  ET_LOCK () ; 
 int /*<<< orphan*/  ET_UNLOCK () ; 
 int /*<<< orphan*/  configtimer (int) ; 
 struct eventtimer* timer ; 

void
cpu_et_frequency(struct eventtimer *et, uint64_t newfreq)
{

	ET_LOCK();
	if (et == timer) {
		configtimer(0);
		et->et_frequency = newfreq;
		configtimer(1);
	} else
		et->et_frequency = newfreq;
	ET_UNLOCK();
}