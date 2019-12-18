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
struct sysc_revision_quirk {scalar_t__ base; scalar_t__ rev_offset; scalar_t__ sysc_offset; scalar_t__ syss_offset; int /*<<< orphan*/  quirks; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  quirks; } ;
struct sysc {scalar_t__ module_pa; scalar_t__* offsets; TYPE_1__ cfg; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct sysc_revision_quirk*) ; 
 size_t SYSC_REVISION ; 
 size_t SYSC_SYSCONFIG ; 
 size_t SYSC_SYSSTATUS ; 
 struct sysc_revision_quirk* sysc_revision_quirks ; 

__attribute__((used)) static void sysc_init_early_quirks(struct sysc *ddata)
{
	const struct sysc_revision_quirk *q;
	int i;

	for (i = 0; i < ARRAY_SIZE(sysc_revision_quirks); i++) {
		q = &sysc_revision_quirks[i];

		if (!q->base)
			continue;

		if (q->base != ddata->module_pa)
			continue;

		if (q->rev_offset >= 0 &&
		    q->rev_offset != ddata->offsets[SYSC_REVISION])
			continue;

		if (q->sysc_offset >= 0 &&
		    q->sysc_offset != ddata->offsets[SYSC_SYSCONFIG])
			continue;

		if (q->syss_offset >= 0 &&
		    q->syss_offset != ddata->offsets[SYSC_SYSSTATUS])
			continue;

		ddata->name = q->name;
		ddata->cfg.quirks |= q->quirks;
	}
}