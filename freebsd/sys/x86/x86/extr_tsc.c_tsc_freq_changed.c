#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_3__ {scalar_t__ freq; } ;
struct cf_level {TYPE_1__ total_set; } ;
struct TYPE_4__ {int tc_frequency; scalar_t__ tc_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_store_rel_64 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ tsc_disabled ; 
 int /*<<< orphan*/  tsc_freq ; 
 TYPE_2__ tsc_timecounter ; 

__attribute__((used)) static void
tsc_freq_changed(void *arg, const struct cf_level *level, int status)
{
	uint64_t freq;

	/* If there was an error during the transition, don't do anything. */
	if (tsc_disabled || status != 0)
		return;

	/* Total setting for this level gives the new frequency in MHz. */
	freq = (uint64_t)level->total_set.freq * 1000000;
	atomic_store_rel_64(&tsc_freq, freq);
	tsc_timecounter.tc_frequency =
	    freq >> (int)(intptr_t)tsc_timecounter.tc_priv;
}