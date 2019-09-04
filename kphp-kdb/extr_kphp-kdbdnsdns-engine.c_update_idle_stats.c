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
struct TYPE_2__ {int workers_max_idle_percent; int workers_average_idle_percent; int workers_max_recent_idle_percent; int workers_recent_idle_percent; } ;

/* Variables and functions */
 int a_idle_quotient ; 
 int a_idle_time ; 
 int now ; 
 int start_time ; 
 int const tot_idle_time ; 
 TYPE_1__ wstat ; 

__attribute__((used)) static void update_idle_stats (void) {
  const int uptime = now - start_time;
  wstat.workers_max_idle_percent = wstat.workers_average_idle_percent = uptime > 0 ? tot_idle_time / uptime * 100 : 0,
  wstat.workers_max_recent_idle_percent = wstat.workers_recent_idle_percent = a_idle_quotient > 0 ? a_idle_time / a_idle_quotient * 100 : a_idle_time;
}