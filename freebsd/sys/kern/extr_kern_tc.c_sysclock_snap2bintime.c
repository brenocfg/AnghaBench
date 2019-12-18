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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct bintime {int /*<<< orphan*/  sec; } ;
struct TYPE_4__ {int /*<<< orphan*/  leapsec_adjustment; int /*<<< orphan*/  period; struct bintime tick_time; int /*<<< orphan*/  period_lerp; struct bintime tick_time_lerp; } ;
struct TYPE_3__ {int th_scale; struct bintime tick_time; } ;
struct sysclock_snap {int delta; TYPE_2__ ff_info; TYPE_1__ fb_info; } ;

/* Variables and functions */
 int EINVAL ; 
 int FBCLOCK_UPTIME ; 
 int FFCLOCK_LEAPSEC ; 
 int FFCLOCK_LERP ; 
 int FFCLOCK_UPTIME ; 
#define  SYSCLOCK_FBCK 129 
#define  SYSCLOCK_FFWD 128 
 int /*<<< orphan*/  bintime_add (struct bintime*,struct bintime*) ; 
 int /*<<< orphan*/  bintime_addx (struct bintime*,int) ; 
 int /*<<< orphan*/  bintime_sub (struct bintime*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffclock_boottime ; 
 int /*<<< orphan*/  ffclock_convert_delta (int,int /*<<< orphan*/ ,struct bintime*) ; 
 int /*<<< orphan*/  getboottimebin (struct bintime*) ; 

int
sysclock_snap2bintime(struct sysclock_snap *cs, struct bintime *bt,
    int whichclock, uint32_t flags)
{
	struct bintime boottimebin;
#ifdef FFCLOCK
	struct bintime bt2;
	uint64_t period;
#endif

	switch (whichclock) {
	case SYSCLOCK_FBCK:
		*bt = cs->fb_info.tick_time;

		/* If snapshot was created with !fast, delta will be >0. */
		if (cs->delta > 0)
			bintime_addx(bt, cs->fb_info.th_scale * cs->delta);

		if ((flags & FBCLOCK_UPTIME) == 0) {
			getboottimebin(&boottimebin);
			bintime_add(bt, &boottimebin);
		}
		break;
#ifdef FFCLOCK
	case SYSCLOCK_FFWD:
		if (flags & FFCLOCK_LERP) {
			*bt = cs->ff_info.tick_time_lerp;
			period = cs->ff_info.period_lerp;
		} else {
			*bt = cs->ff_info.tick_time;
			period = cs->ff_info.period;
		}

		/* If snapshot was created with !fast, delta will be >0. */
		if (cs->delta > 0) {
			ffclock_convert_delta(cs->delta, period, &bt2);
			bintime_add(bt, &bt2);
		}

		/* Leap second adjustment. */
		if (flags & FFCLOCK_LEAPSEC)
			bt->sec -= cs->ff_info.leapsec_adjustment;

		/* Boot time adjustment, for uptime/monotonic clocks. */
		if (flags & FFCLOCK_UPTIME)
			bintime_sub(bt, &ffclock_boottime);
		break;
#endif
	default:
		return (EINVAL);
		break;
	}

	return (0);
}