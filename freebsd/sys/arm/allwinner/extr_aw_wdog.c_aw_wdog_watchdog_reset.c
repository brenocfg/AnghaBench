#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int wdog_mode_intvl_shift; int wdog_mode_en; int wdog_config_value; int wdog_ctrl_key; scalar_t__ wdog_ctrl; scalar_t__ wdog_config; scalar_t__ wdog_mode; } ;
struct TYPE_4__ {int value; } ;

/* Variables and functions */
 int WDOG_CTRL_RESTART ; 
 int /*<<< orphan*/  WRITE (TYPE_2__*,scalar_t__,int) ; 
 TYPE_2__* aw_wdog_sc ; 
 int /*<<< orphan*/  printf (char*) ; 
 TYPE_1__* wd_intervals ; 

void
aw_wdog_watchdog_reset(void)
{

	if (aw_wdog_sc == NULL) {
		printf("Reset: watchdog device has not been initialized\n");
		return;
	}

	WRITE(aw_wdog_sc, aw_wdog_sc->wdog_mode,
	    (wd_intervals[0].value << aw_wdog_sc->wdog_mode_intvl_shift) |
	    aw_wdog_sc->wdog_mode_en);
	if (aw_wdog_sc->wdog_config)
		WRITE(aw_wdog_sc, aw_wdog_sc->wdog_config,
		      aw_wdog_sc->wdog_config_value);
	WRITE(aw_wdog_sc, aw_wdog_sc->wdog_ctrl,
	    WDOG_CTRL_RESTART | aw_wdog_sc->wdog_ctrl_key);
	while(1)
		;

}