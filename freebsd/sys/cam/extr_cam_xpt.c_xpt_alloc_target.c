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
typedef  scalar_t__ target_id_t ;
struct cam_et {scalar_t__ target_id; int refcount; int /*<<< orphan*/  last_reset; int /*<<< orphan*/  luns_mtx; int /*<<< orphan*/ * luns; scalar_t__ generation; struct cam_eb* bus; int /*<<< orphan*/  ed_entries; } ;
struct cam_eb {int /*<<< orphan*/  generation; int /*<<< orphan*/  et_entries; int /*<<< orphan*/  refcount; int /*<<< orphan*/  eb_mtx; } ;
struct TYPE_2__ {int /*<<< orphan*/  xpt_topo_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_CAMXPT ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 struct cam_et* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_BEFORE (struct cam_et*,struct cam_et*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct cam_et*,int /*<<< orphan*/ ) ; 
 struct cam_et* TAILQ_NEXT (struct cam_et*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevalclear (int /*<<< orphan*/ *) ; 
 TYPE_1__ xsoftc ; 

__attribute__((used)) static struct cam_et *
xpt_alloc_target(struct cam_eb *bus, target_id_t target_id)
{
	struct cam_et *cur_target, *target;

	mtx_assert(&xsoftc.xpt_topo_lock, MA_OWNED);
	mtx_assert(&bus->eb_mtx, MA_OWNED);
	target = (struct cam_et *)malloc(sizeof(*target), M_CAMXPT,
					 M_NOWAIT|M_ZERO);
	if (target == NULL)
		return (NULL);

	TAILQ_INIT(&target->ed_entries);
	target->bus = bus;
	target->target_id = target_id;
	target->refcount = 1;
	target->generation = 0;
	target->luns = NULL;
	mtx_init(&target->luns_mtx, "CAM LUNs lock", NULL, MTX_DEF);
	timevalclear(&target->last_reset);
	/*
	 * Hold a reference to our parent bus so it
	 * will not go away before we do.
	 */
	bus->refcount++;

	/* Insertion sort into our bus's target list */
	cur_target = TAILQ_FIRST(&bus->et_entries);
	while (cur_target != NULL && cur_target->target_id < target_id)
		cur_target = TAILQ_NEXT(cur_target, links);
	if (cur_target != NULL) {
		TAILQ_INSERT_BEFORE(cur_target, target, links);
	} else {
		TAILQ_INSERT_TAIL(&bus->et_entries, target, links);
	}
	bus->generation++;
	return (target);
}