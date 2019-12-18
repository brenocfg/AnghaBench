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
struct devfreq_event_dev {TYPE_1__* desc; } ;
struct TYPE_5__ {int id; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int EINVAL ; 
 TYPE_2__* ppmu_events ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int exynos_ppmu_find_ppmu_id(struct devfreq_event_dev *edev)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(ppmu_events); i++)
		if (!strcmp(edev->desc->name, ppmu_events[i].name))
			return ppmu_events[i].id;

	return -EINVAL;
}