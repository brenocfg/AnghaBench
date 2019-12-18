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
struct net_device {int dummy; } ;
struct ag71xx {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 struct ag71xx* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ag71xx_oom_timer_handler(unsigned long data)
{
	struct net_device *dev = (struct net_device *) data;
	struct ag71xx *ag = netdev_priv(dev);

	napi_schedule(&ag->napi);
}