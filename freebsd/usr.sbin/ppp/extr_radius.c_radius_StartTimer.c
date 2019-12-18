#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* name; int load; struct bundle* arg; int /*<<< orphan*/  (* func ) (struct bundle*) ;} ;
struct TYPE_7__ {int interval; TYPE_1__ timer; } ;
struct TYPE_6__ {scalar_t__* file; } ;
struct TYPE_8__ {TYPE_3__ alive; TYPE_2__ cfg; } ;
struct bundle {TYPE_4__ radius; } ;

/* Variables and functions */
 int SECTICKS ; 
 int /*<<< orphan*/  radius_alive (struct bundle*) ; 

void
radius_StartTimer(struct bundle *bundle)
{
  if (*bundle->radius.cfg.file && bundle->radius.alive.interval) {
    bundle->radius.alive.timer.func = radius_alive;
    bundle->radius.alive.timer.name = "radius alive";
    bundle->radius.alive.timer.load = bundle->radius.alive.interval * SECTICKS;
    bundle->radius.alive.timer.arg = bundle;
    radius_alive(bundle);
  }
}