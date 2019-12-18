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
struct subsys_interface {int /*<<< orphan*/  (* remove_dev ) (struct device*,struct subsys_interface*) ;int /*<<< orphan*/  node; struct bus_type* subsys; } ;
struct subsys_dev_iter {int dummy; } ;
struct device {int dummy; } ;
struct bus_type {TYPE_1__* p; } ;
struct TYPE_2__ {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_put (struct bus_type*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct device*,struct subsys_interface*) ; 
 int /*<<< orphan*/  subsys_dev_iter_exit (struct subsys_dev_iter*) ; 
 int /*<<< orphan*/  subsys_dev_iter_init (struct subsys_dev_iter*,struct bus_type*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct device* subsys_dev_iter_next (struct subsys_dev_iter*) ; 

void subsys_interface_unregister(struct subsys_interface *sif)
{
	struct bus_type *subsys;
	struct subsys_dev_iter iter;
	struct device *dev;

	if (!sif || !sif->subsys)
		return;

	subsys = sif->subsys;

	mutex_lock(&subsys->p->mutex);
	list_del_init(&sif->node);
	if (sif->remove_dev) {
		subsys_dev_iter_init(&iter, subsys, NULL, NULL);
		while ((dev = subsys_dev_iter_next(&iter)))
			sif->remove_dev(dev, sif);
		subsys_dev_iter_exit(&iter);
	}
	mutex_unlock(&subsys->p->mutex);

	bus_put(subsys);
}