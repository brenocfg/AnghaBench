#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int et_flags; } ;

/* Variables and functions */
 int ET_FLAGS_ONESHOT ; 
 int ET_FLAGS_PERIODIC ; 
 int /*<<< orphan*/  MAX (int,int) ; 
 int MIN (int /*<<< orphan*/ ,int) ; 
 int SBT_1S ; 
 int hz ; 
 int periodic ; 
 int profhz ; 
 scalar_t__ profiling ; 
 int round_freq (TYPE_1__*,int) ; 
 int singlemul ; 
 int stathz ; 
 TYPE_1__* timer ; 
 int timerperiod ; 

__attribute__((used)) static void
setuptimer(void)
{
	int freq;

	if (periodic && (timer->et_flags & ET_FLAGS_PERIODIC) == 0)
		periodic = 0;
	else if (!periodic && (timer->et_flags & ET_FLAGS_ONESHOT) == 0)
		periodic = 1;
	singlemul = MIN(MAX(singlemul, 1), 20);
	freq = hz * singlemul;
	while (freq < (profiling ? profhz : stathz))
		freq += hz;
	freq = round_freq(timer, freq);
	timerperiod = SBT_1S / freq;
}