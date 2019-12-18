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
struct oidset {int dummy; } ;
struct combine_filter_data {size_t nr; TYPE_1__* sub; } ;
struct TYPE_2__ {int /*<<< orphan*/  omits; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_all (struct oidset*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidset_clear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void filter_combine__finalize_omits(
	struct oidset *omits,
	void *filter_data)
{
	struct combine_filter_data *d = filter_data;
	size_t sub;

	for (sub = 0; sub < d->nr; sub++) {
		add_all(omits, &d->sub[sub].omits);
		oidset_clear(&d->sub[sub].omits);
	}
}