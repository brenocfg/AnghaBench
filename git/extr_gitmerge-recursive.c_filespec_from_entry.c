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
struct stage_data {TYPE_1__* stages; } ;
struct object_id {int dummy; } ;
struct diff_filespec {unsigned int mode; int /*<<< orphan*/  oid; } ;
struct TYPE_2__ {unsigned int mode; struct object_id oid; } ;

/* Variables and functions */
 scalar_t__ is_null_oid (struct object_id*) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,struct object_id*) ; 

__attribute__((used)) static struct diff_filespec *filespec_from_entry(struct diff_filespec *target,
						 struct stage_data *entry,
						 int stage)
{
	struct object_id *oid = &entry->stages[stage].oid;
	unsigned mode = entry->stages[stage].mode;
	if (mode == 0 || is_null_oid(oid))
		return NULL;
	oidcpy(&target->oid, oid);
	target->mode = mode;
	return target;
}