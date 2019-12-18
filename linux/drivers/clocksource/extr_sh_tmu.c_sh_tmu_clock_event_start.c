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
struct sh_tmu_channel {int periodic; TYPE_1__* tmu; } ;
struct TYPE_2__ {int rate; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  sh_tmu_enable (struct sh_tmu_channel*) ; 
 int /*<<< orphan*/  sh_tmu_set_next (struct sh_tmu_channel*,int,int) ; 

__attribute__((used)) static void sh_tmu_clock_event_start(struct sh_tmu_channel *ch, int periodic)
{
	sh_tmu_enable(ch);

	if (periodic) {
		ch->periodic = (ch->tmu->rate + HZ/2) / HZ;
		sh_tmu_set_next(ch, ch->periodic, 1);
	}
}