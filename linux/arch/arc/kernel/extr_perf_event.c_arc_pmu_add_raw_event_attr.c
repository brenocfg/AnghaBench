#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_4__* attr; TYPE_2__** attrs; TYPE_1__* raw_entry; } ;
struct TYPE_7__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {TYPE_2__ attr; int /*<<< orphan*/  show; } ;
struct TYPE_9__ {int id; TYPE_3__ attr; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ ARCPMU_EVENT_NAME_LEN ; 
 int /*<<< orphan*/  VERIFY_OCTAL_PERMISSIONS (int) ; 
 TYPE_5__* arc_pmu ; 
 int /*<<< orphan*/  arc_pmu_events_sysfs_show ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static void arc_pmu_add_raw_event_attr(int j, char *str)
{
	memmove(arc_pmu->raw_entry[j].name, str, ARCPMU_EVENT_NAME_LEN - 1);
	arc_pmu->attr[j].attr.attr.name = arc_pmu->raw_entry[j].name;
	arc_pmu->attr[j].attr.attr.mode = VERIFY_OCTAL_PERMISSIONS(0444);
	arc_pmu->attr[j].attr.show = arc_pmu_events_sysfs_show;
	arc_pmu->attr[j].id = j;
	arc_pmu->attrs[j] = &(arc_pmu->attr[j].attr.attr);
}