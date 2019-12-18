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
struct scb {int flags; struct scb* col_scb; TYPE_1__* hscb; } ;
struct TYPE_5__ {int /*<<< orphan*/  any_dev_free_scb_list; int /*<<< orphan*/ ** scbindex; } ;
struct ahd_softc {TYPE_2__ scb_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  le; } ;
struct TYPE_4__ {int control; } ;

/* Variables and functions */
 int /*<<< orphan*/  AHD_GET_SCB_COL_IDX (struct ahd_softc*,struct scb*) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct scb*,int /*<<< orphan*/ ) ; 
 int SCB_ACTIVE ; 
 int SCB_FLAG_NONE ; 
 size_t SCB_GET_TAG (struct scb*) ; 
 int SCB_ON_COL_LIST ; 
 int SCB_PACKETIZED ; 
 int TAG_ENB ; 
 int /*<<< orphan*/  ahd_add_col_list (struct ahd_softc*,struct scb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_rem_col_list (struct ahd_softc*,struct scb*) ; 
 int /*<<< orphan*/  aic_platform_scb_free (struct ahd_softc*,struct scb*) ; 
 TYPE_3__ links ; 

void
ahd_free_scb(struct ahd_softc *ahd, struct scb *scb)
{       

	/* Clean up for the next user */
	scb->flags = SCB_FLAG_NONE;
	scb->hscb->control = 0;
	ahd->scb_data.scbindex[SCB_GET_TAG(scb)] = NULL;

	if (scb->col_scb == NULL) {

		/*
		 * No collision possible.  Just free normally.
		 */
		LIST_INSERT_HEAD(&ahd->scb_data.any_dev_free_scb_list,
				 scb, links.le);
	} else if ((scb->col_scb->flags & SCB_ON_COL_LIST) != 0) {

		/*
		 * The SCB we might have collided with is on
		 * a free collision list.  Put both SCBs on
		 * the generic list.
		 */
		ahd_rem_col_list(ahd, scb->col_scb);
		LIST_INSERT_HEAD(&ahd->scb_data.any_dev_free_scb_list,
				 scb, links.le);
		LIST_INSERT_HEAD(&ahd->scb_data.any_dev_free_scb_list,
				 scb->col_scb, links.le);
	} else if ((scb->col_scb->flags
		  & (SCB_PACKETIZED|SCB_ACTIVE)) == SCB_ACTIVE
		&& (scb->col_scb->hscb->control & TAG_ENB) != 0) {

		/*
		 * The SCB we might collide with on the next allocation
		 * is still active in a non-packetized, tagged, context.
		 * Put us on the SCB collision list.
		 */
		ahd_add_col_list(ahd, scb,
				 AHD_GET_SCB_COL_IDX(ahd, scb->col_scb));
	} else {
		/*
		 * The SCB we might collide with on the next allocation
		 * is either active in a packetized context, or free.
		 * Since we can't collide, put this SCB on the generic
		 * free list.
		 */
		LIST_INSERT_HEAD(&ahd->scb_data.any_dev_free_scb_list,
				 scb, links.le);
	}

	aic_platform_scb_free(ahd, scb);
}