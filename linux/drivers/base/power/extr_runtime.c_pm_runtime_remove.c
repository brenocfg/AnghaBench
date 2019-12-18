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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pm_runtime_disable (struct device*,int) ; 
 int /*<<< orphan*/  pm_runtime_reinit (struct device*) ; 

void pm_runtime_remove(struct device *dev)
{
	__pm_runtime_disable(dev, false);
	pm_runtime_reinit(dev);
}