#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int load; } ;
struct TYPE_9__ {int interval; TYPE_4__ timer; } ;
struct TYPE_11__ {TYPE_3__ alive; } ;
struct TYPE_7__ {int /*<<< orphan*/  throughput; } ;
struct TYPE_8__ {TYPE_1__ ipcp; } ;
struct bundle {TYPE_6__ radius; TYPE_2__ ncp; int /*<<< orphan*/  links; int /*<<< orphan*/  radacct; } ;

/* Variables and functions */
 int /*<<< orphan*/  RAD_ALIVE ; 
 int SECTICKS ; 
 int /*<<< orphan*/  radius_Account (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_Start (TYPE_4__*) ; 
 int /*<<< orphan*/  timer_Stop (TYPE_4__*) ; 

__attribute__((used)) static void
radius_alive(void *v)
{
  struct bundle *bundle = (struct bundle *)v;

  timer_Stop(&bundle->radius.alive.timer);
  bundle->radius.alive.timer.load = bundle->radius.alive.interval * SECTICKS;
  if (bundle->radius.alive.timer.load) {
    radius_Account(&bundle->radius, &bundle->radacct,
                   bundle->links, RAD_ALIVE, &bundle->ncp.ipcp.throughput);
    timer_Start(&bundle->radius.alive.timer);
  }
}