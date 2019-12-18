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
struct rerere_id {int variant; struct rerere_dir* collection; } ;
struct rerere_dir {int status_nr; int /*<<< orphan*/ * status; } ;

/* Variables and functions */
 int /*<<< orphan*/  fit_variant (struct rerere_dir*,int) ; 

__attribute__((used)) static void assign_variant(struct rerere_id *id)
{
	int variant;
	struct rerere_dir *rr_dir = id->collection;

	variant = id->variant;
	if (variant < 0) {
		for (variant = 0; variant < rr_dir->status_nr; variant++)
			if (!rr_dir->status[variant])
				break;
	}
	fit_variant(rr_dir, variant);
	id->variant = variant;
}