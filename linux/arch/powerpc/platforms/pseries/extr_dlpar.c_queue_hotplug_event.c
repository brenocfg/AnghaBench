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
struct work_struct {int dummy; } ;
struct pseries_hp_work {struct pseries_hp_errorlog* errlog; } ;
struct pseries_hp_errorlog {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (struct work_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct pseries_hp_errorlog*) ; 
 struct pseries_hp_work* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct pseries_hp_errorlog* kmemdup (struct pseries_hp_errorlog*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pseries_hp_work_fn ; 
 int /*<<< orphan*/  pseries_hp_wq ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,struct work_struct*) ; 

void queue_hotplug_event(struct pseries_hp_errorlog *hp_errlog)
{
	struct pseries_hp_work *work;
	struct pseries_hp_errorlog *hp_errlog_copy;

	hp_errlog_copy = kmemdup(hp_errlog, sizeof(*hp_errlog), GFP_ATOMIC);
	if (!hp_errlog_copy)
		return;

	work = kmalloc(sizeof(struct pseries_hp_work), GFP_ATOMIC);
	if (work) {
		INIT_WORK((struct work_struct *)work, pseries_hp_work_fn);
		work->errlog = hp_errlog_copy;
		queue_work(pseries_hp_wq, (struct work_struct *)work);
	} else {
		kfree(hp_errlog_copy);
	}
}