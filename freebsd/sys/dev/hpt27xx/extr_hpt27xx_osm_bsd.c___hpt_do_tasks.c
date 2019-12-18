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
struct TYPE_5__ {int /*<<< orphan*/  data; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;struct TYPE_5__* next; } ;
struct TYPE_4__ {int /*<<< orphan*/  vbus; TYPE_2__* tasks; } ;
typedef  TYPE_1__* PVBUS_EXT ;
typedef  TYPE_2__ OSM_TASK ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __hpt_do_tasks(PVBUS_EXT vbus_ext)
{
	OSM_TASK *tasks;

	tasks = vbus_ext->tasks;
	vbus_ext->tasks = 0;

	while (tasks) {
		OSM_TASK *t = tasks;
		tasks = t->next;
		t->next = 0;
		t->func(vbus_ext->vbus, t->data);
	}
}