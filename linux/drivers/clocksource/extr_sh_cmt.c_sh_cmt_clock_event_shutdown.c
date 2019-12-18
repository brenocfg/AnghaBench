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
struct sh_cmt_channel {int dummy; } ;
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_CLOCKEVENT ; 
 struct sh_cmt_channel* ced_to_sh_cmt (struct clock_event_device*) ; 
 int /*<<< orphan*/  sh_cmt_stop (struct sh_cmt_channel*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh_cmt_clock_event_shutdown(struct clock_event_device *ced)
{
	struct sh_cmt_channel *ch = ced_to_sh_cmt(ced);

	sh_cmt_stop(ch, FLAG_CLOCKEVENT);
	return 0;
}