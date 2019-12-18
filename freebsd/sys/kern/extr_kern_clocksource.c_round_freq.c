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
struct eventtimer {int et_frequency; int et_flags; scalar_t__ et_min_period; scalar_t__ et_max_period; int /*<<< orphan*/  et_name; } ;

/* Variables and functions */
 int ET_FLAGS_POW2DIV ; 
 int /*<<< orphan*/  SBT2FREQ (scalar_t__) ; 
 scalar_t__ SBT_1S ; 
 int flsl (int) ; 
 int lmax (int,int) ; 
 int max (int,int /*<<< orphan*/ ) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
round_freq(struct eventtimer *et, int freq)
{
	uint64_t div;

	if (et->et_frequency != 0) {
		div = lmax((et->et_frequency + freq / 2) / freq, 1);
		if (et->et_flags & ET_FLAGS_POW2DIV)
			div = 1 << (flsl(div + div / 2) - 1);
		freq = (et->et_frequency + div / 2) / div;
	}
	if (et->et_min_period > SBT_1S)
		panic("Event timer \"%s\" doesn't support sub-second periods!",
		    et->et_name);
	else if (et->et_min_period != 0)
		freq = min(freq, SBT2FREQ(et->et_min_period));
	if (et->et_max_period < SBT_1S && et->et_max_period != 0)
		freq = max(freq, SBT2FREQ(et->et_max_period));
	return (freq);
}