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
struct os_reltime {int usec; int /*<<< orphan*/  sec; } ;
struct sta_info {struct os_reltime backlogged_until; } ;
struct hostapd_data {TYPE_1__* iconf; } ;
struct TYPE_2__ {int airtime_update_interval; } ;

/* Variables and functions */
 int AIRTIME_BACKLOG_EXPIRY_FACTOR ; 

__attribute__((used)) static void set_new_backlog_time(struct hostapd_data *hapd,
				 struct sta_info *sta,
				 struct os_reltime *now)
{
	sta->backlogged_until = *now;
	sta->backlogged_until.usec += hapd->iconf->airtime_update_interval *
		AIRTIME_BACKLOG_EXPIRY_FACTOR;
	while (sta->backlogged_until.usec >= 1000000) {
		sta->backlogged_until.sec++;
		sta->backlogged_until.usec -= 1000000;
	}
}