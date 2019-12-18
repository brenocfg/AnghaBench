#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct combine_filter_data {size_t nr; TYPE_3__* sub; } ;
struct TYPE_4__ {scalar_t__ size; } ;
struct TYPE_5__ {TYPE_1__ set; } ;
struct TYPE_6__ {TYPE_2__ omits; int /*<<< orphan*/  seen; int /*<<< orphan*/  filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  list_objects_filter__free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oidset_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void filter_combine__free(void *filter_data)
{
	struct combine_filter_data *d = filter_data;
	size_t sub;
	for (sub = 0; sub < d->nr; sub++) {
		list_objects_filter__free(d->sub[sub].filter);
		oidset_clear(&d->sub[sub].seen);
		if (d->sub[sub].omits.set.size)
			BUG("expected oidset to be cleared already");
	}
	free(d->sub);
}