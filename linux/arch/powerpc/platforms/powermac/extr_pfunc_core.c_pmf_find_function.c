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
struct pmf_function {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMF_FLAGS_ON_DEMAND ; 
 struct pmf_function* __pmf_find_function (struct device_node*,char const*,int /*<<< orphan*/ ) ; 
 struct pmf_function* pmf_get_function (struct pmf_function*) ; 
 int /*<<< orphan*/  pmf_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct pmf_function *pmf_find_function(struct device_node *target,
				       const char *name)
{
	struct pmf_function *func;
	unsigned long flags;

	spin_lock_irqsave(&pmf_lock, flags);
	func = __pmf_find_function(target, name, PMF_FLAGS_ON_DEMAND);
	if (func)
		func = pmf_get_function(func);
	spin_unlock_irqrestore(&pmf_lock, flags);
	return func;
}