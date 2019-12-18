#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pm_qos_constraints {void* type; int /*<<< orphan*/  no_constraint_value; void* default_value; void* target_value; int /*<<< orphan*/  list; struct blocking_notifier_head* notifiers; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; struct dev_pm_qos* qos; } ;
struct device {TYPE_2__ power; } ;
struct TYPE_3__ {int /*<<< orphan*/  list; } ;
struct dev_pm_qos {TYPE_1__ flags; struct pm_qos_constraints latency_tolerance; struct pm_qos_constraints resume_latency; } ;
struct blocking_notifier_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCKING_INIT_NOTIFIER_HEAD (struct blocking_notifier_head*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 void* PM_QOS_LATENCY_TOLERANCE_DEFAULT_VALUE ; 
 int /*<<< orphan*/  PM_QOS_LATENCY_TOLERANCE_NO_CONSTRAINT ; 
 void* PM_QOS_MIN ; 
 void* PM_QOS_RESUME_LATENCY_DEFAULT_VALUE ; 
 int /*<<< orphan*/  PM_QOS_RESUME_LATENCY_NO_CONSTRAINT ; 
 int /*<<< orphan*/  kfree (struct dev_pm_qos*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plist_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dev_pm_qos_constraints_allocate(struct device *dev)
{
	struct dev_pm_qos *qos;
	struct pm_qos_constraints *c;
	struct blocking_notifier_head *n;

	qos = kzalloc(sizeof(*qos), GFP_KERNEL);
	if (!qos)
		return -ENOMEM;

	n = kzalloc(3 * sizeof(*n), GFP_KERNEL);
	if (!n) {
		kfree(qos);
		return -ENOMEM;
	}

	c = &qos->resume_latency;
	plist_head_init(&c->list);
	c->target_value = PM_QOS_RESUME_LATENCY_DEFAULT_VALUE;
	c->default_value = PM_QOS_RESUME_LATENCY_DEFAULT_VALUE;
	c->no_constraint_value = PM_QOS_RESUME_LATENCY_NO_CONSTRAINT;
	c->type = PM_QOS_MIN;
	c->notifiers = n;
	BLOCKING_INIT_NOTIFIER_HEAD(n);

	c = &qos->latency_tolerance;
	plist_head_init(&c->list);
	c->target_value = PM_QOS_LATENCY_TOLERANCE_DEFAULT_VALUE;
	c->default_value = PM_QOS_LATENCY_TOLERANCE_DEFAULT_VALUE;
	c->no_constraint_value = PM_QOS_LATENCY_TOLERANCE_NO_CONSTRAINT;
	c->type = PM_QOS_MIN;

	INIT_LIST_HEAD(&qos->flags.list);

	spin_lock_irq(&dev->power.lock);
	dev->power.qos = qos;
	spin_unlock_irq(&dev->power.lock);

	return 0;
}