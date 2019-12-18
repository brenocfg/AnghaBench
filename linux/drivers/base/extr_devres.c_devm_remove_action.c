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
struct action_devres {void* data; void (* action ) (void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_action_match ; 
 int /*<<< orphan*/  devm_action_release ; 
 int /*<<< orphan*/  devres_destroy (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct action_devres*) ; 

void devm_remove_action(struct device *dev, void (*action)(void *), void *data)
{
	struct action_devres devres = {
		.data = data,
		.action = action,
	};

	WARN_ON(devres_destroy(dev, devm_action_release, devm_action_match,
			       &devres));
}