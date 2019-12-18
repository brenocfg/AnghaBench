#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  min_nr; } ;
struct TYPE_3__ {scalar_t__ min_nr; } ;
struct bio_set {int /*<<< orphan*/  front_pad; TYPE_2__ bio_pool; scalar_t__ rescue_workqueue; TYPE_1__ bvec_pool; } ;

/* Variables and functions */
 int BIOSET_NEED_BVECS ; 
 int BIOSET_NEED_RESCUER ; 
 int bioset_init (struct bio_set*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int bioset_init_from_src(struct bio_set *bs, struct bio_set *src)
{
	int flags;

	flags = 0;
	if (src->bvec_pool.min_nr)
		flags |= BIOSET_NEED_BVECS;
	if (src->rescue_workqueue)
		flags |= BIOSET_NEED_RESCUER;

	return bioset_init(bs, src->bio_pool.min_nr, src->front_pad, flags);
}