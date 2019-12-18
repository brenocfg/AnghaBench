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
struct sh_tmu_channel {int cs_enabled; } ;
struct clocksource {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 struct sh_tmu_channel* cs_to_sh_tmu (struct clocksource*) ; 
 int /*<<< orphan*/  sh_tmu_disable (struct sh_tmu_channel*) ; 

__attribute__((used)) static void sh_tmu_clocksource_disable(struct clocksource *cs)
{
	struct sh_tmu_channel *ch = cs_to_sh_tmu(cs);

	if (WARN_ON(!ch->cs_enabled))
		return;

	sh_tmu_disable(ch);
	ch->cs_enabled = false;
}