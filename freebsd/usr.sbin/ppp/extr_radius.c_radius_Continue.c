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
struct timeval {int tv_usec; int tv_sec; } ;
struct TYPE_5__ {int load; } ;
struct TYPE_4__ {TYPE_2__ timer; int /*<<< orphan*/  fd; int /*<<< orphan*/  rad; } ;
struct radius {TYPE_1__ cx; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogPHASE ; 
 int /*<<< orphan*/  LogRADIUS ; 
 int SECTICKS ; 
 int TICKUNIT ; 
 scalar_t__ log_IsKept (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*) ; 
 int rad_continue_send_request (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  radius_Process (struct radius*,int) ; 
 int /*<<< orphan*/  timer_Start (TYPE_2__*) ; 
 int /*<<< orphan*/  timer_Stop (TYPE_2__*) ; 

__attribute__((used)) static void
radius_Continue(struct radius *r, int sel)
{
  struct timeval tv;
  int got;

  timer_Stop(&r->cx.timer);
  if ((got = rad_continue_send_request(r->cx.rad, sel, &r->cx.fd, &tv)) == 0) {
    log_Printf(log_IsKept(LogRADIUS) ? LogRADIUS : LogPHASE,
	       "Radius: Request re-sent\n");
    r->cx.timer.load = tv.tv_usec / TICKUNIT + tv.tv_sec * SECTICKS;
    timer_Start(&r->cx.timer);
    return;
  }

  radius_Process(r, got);
}