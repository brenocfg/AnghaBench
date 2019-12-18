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
struct vi_info {int /*<<< orphan*/  tick; TYPE_1__* pi; } ;
struct adapter {int dummy; } ;
struct TYPE_2__ {struct adapter* adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_schedule (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  vi_refresh_stats (struct adapter*,struct vi_info*) ; 

void
vi_tick(void *arg)
{
	struct vi_info *vi = arg;
	struct adapter *sc = vi->pi->adapter;

	vi_refresh_stats(sc, vi);

	callout_schedule(&vi->tick, hz);
}