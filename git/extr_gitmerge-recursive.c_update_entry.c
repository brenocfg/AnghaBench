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
struct stage_data {TYPE_1__* stages; scalar_t__ processed; } ;
struct diff_filespec {int /*<<< orphan*/  oid; int /*<<< orphan*/  mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  oid; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_entry(struct stage_data *entry,
			 struct diff_filespec *o,
			 struct diff_filespec *a,
			 struct diff_filespec *b)
{
	entry->processed = 0;
	entry->stages[1].mode = o->mode;
	entry->stages[2].mode = a->mode;
	entry->stages[3].mode = b->mode;
	oidcpy(&entry->stages[1].oid, &o->oid);
	oidcpy(&entry->stages[2].oid, &a->oid);
	oidcpy(&entry->stages[3].oid, &b->oid);
}