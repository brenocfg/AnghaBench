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
struct sh_cmt_channel {int cs_enabled; scalar_t__ total_cycles; } ;
struct clocksource {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_CLOCKSOURCE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct sh_cmt_channel* cs_to_sh_cmt (struct clocksource*) ; 
 int sh_cmt_start (struct sh_cmt_channel*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh_cmt_clocksource_enable(struct clocksource *cs)
{
	int ret;
	struct sh_cmt_channel *ch = cs_to_sh_cmt(cs);

	WARN_ON(ch->cs_enabled);

	ch->total_cycles = 0;

	ret = sh_cmt_start(ch, FLAG_CLOCKSOURCE);
	if (!ret)
		ch->cs_enabled = true;

	return ret;
}