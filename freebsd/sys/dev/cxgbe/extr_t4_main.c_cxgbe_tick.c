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
struct port_info {int /*<<< orphan*/  tick; struct adapter* adapter; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_LOCK_ASSERT_OWNED (struct port_info*) ; 
 int /*<<< orphan*/  callout_schedule (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgbe_refresh_stats (struct adapter*,struct port_info*) ; 
 int /*<<< orphan*/  hz ; 

__attribute__((used)) static void
cxgbe_tick(void *arg)
{
	struct port_info *pi = arg;
	struct adapter *sc = pi->adapter;

	PORT_LOCK_ASSERT_OWNED(pi);
	cxgbe_refresh_stats(sc, pi);

	callout_schedule(&pi->tick, hz);
}