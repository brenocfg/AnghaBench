#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * ddpa_clone; int /*<<< orphan*/ * origin_origin; int /*<<< orphan*/  origin_snaps; int /*<<< orphan*/  clone_snaps; int /*<<< orphan*/  shared_snaps; } ;
typedef  TYPE_1__ dsl_dataset_promote_arg_t ;

/* Variables and functions */
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  snaplist_destroy (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void
promote_rele(dsl_dataset_promote_arg_t *ddpa, void *tag)
{
	snaplist_destroy(&ddpa->shared_snaps, tag);
	snaplist_destroy(&ddpa->clone_snaps, tag);
	snaplist_destroy(&ddpa->origin_snaps, tag);
	if (ddpa->origin_origin != NULL)
		dsl_dataset_rele(ddpa->origin_origin, tag);
	dsl_dataset_rele(ddpa->ddpa_clone, tag);
}