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
typedef  size_t u_int ;
struct scb_tailq {int dummy; } ;
struct scb_list {int dummy; } ;
struct scb {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {struct scb_tailq free_scbs; struct scb_list* free_scb_lists; } ;
struct ahd_softc {TYPE_1__ scb_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  tqe; } ;

/* Variables and functions */
 size_t AHD_GET_SCB_COL_IDX (struct ahd_softc*,struct scb*) ; 
 struct scb* LIST_FIRST (struct scb_list*) ; 
 struct scb* LIST_NEXT (struct scb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct scb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCB_ON_COL_LIST ; 
 int /*<<< orphan*/  TAILQ_INSERT_AFTER (struct scb_tailq*,struct scb*,struct scb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct scb_tailq*,struct scb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  collision_links ; 
 TYPE_2__ links ; 

__attribute__((used)) static void
ahd_rem_col_list(struct ahd_softc *ahd, struct scb *scb)
{
	struct	scb_list *free_list;
	struct	scb_tailq *free_tailq;
	struct	scb *first_scb;
	u_int	col_idx;

	scb->flags &= ~SCB_ON_COL_LIST;
	col_idx = AHD_GET_SCB_COL_IDX(ahd, scb);
	free_list = &ahd->scb_data.free_scb_lists[col_idx];
	free_tailq = &ahd->scb_data.free_scbs;
	first_scb = LIST_FIRST(free_list);
	if (first_scb == scb) {
		struct scb *next_scb;

		/*
		 * Maintain order in the collision free
		 * lists for fairness if this device has
		 * other colliding tags active.
		 */
		next_scb = LIST_NEXT(scb, collision_links);
		if (next_scb != NULL) {
			TAILQ_INSERT_AFTER(free_tailq, scb,
					   next_scb, links.tqe);
		}
		TAILQ_REMOVE(free_tailq, scb, links.tqe);
	}
	LIST_REMOVE(scb, collision_links);
}