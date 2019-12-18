#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int load; char* name; int /*<<< orphan*/  func; struct hdlc* arg; } ;
struct hdlc {TYPE_1__ ReportTimer; } ;

/* Variables and functions */
 int SECTICKS ; 
 int /*<<< orphan*/  hdlc_ReportTime ; 
 int /*<<< orphan*/  timer_Start (TYPE_1__*) ; 
 int /*<<< orphan*/  timer_Stop (TYPE_1__*) ; 

void
hdlc_StartTimer(struct hdlc *hdlc)
{
  timer_Stop(&hdlc->ReportTimer);
  hdlc->ReportTimer.load = 60 * SECTICKS;
  hdlc->ReportTimer.arg = hdlc;
  hdlc->ReportTimer.func = hdlc_ReportTime;
  hdlc->ReportTimer.name = "hdlc";
  timer_Start(&hdlc->ReportTimer);
}