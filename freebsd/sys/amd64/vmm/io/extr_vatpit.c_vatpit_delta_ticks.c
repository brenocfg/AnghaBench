#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_2__ {int frac; } ;
struct vatpit {TYPE_1__ freq_bt; } ;
struct channel {int /*<<< orphan*/  now_bt; } ;
struct bintime {int sec; int frac; } ;

/* Variables and functions */
 int PIT_8254_FREQ ; 
 int /*<<< orphan*/  bintime_sub (struct bintime*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  binuptime (struct bintime*) ; 

__attribute__((used)) static uint64_t
vatpit_delta_ticks(struct vatpit *vatpit, struct channel *c)
{
	struct bintime delta;
	uint64_t result;

	binuptime(&delta);
	bintime_sub(&delta, &c->now_bt);

	result = delta.sec * PIT_8254_FREQ;
	result += delta.frac / vatpit->freq_bt.frac;

	return (result);
}