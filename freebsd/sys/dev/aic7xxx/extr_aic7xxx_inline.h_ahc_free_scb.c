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
struct scb {int /*<<< orphan*/  flags; struct hardware_scb* hscb; } ;
struct hardware_scb {size_t tag; scalar_t__ control; } ;
struct ahc_softc {TYPE_1__* scb_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  sle; } ;
struct TYPE_3__ {int /*<<< orphan*/  free_scbs; int /*<<< orphan*/ ** scbindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCB_FLAG_NONE ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct scb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aic_platform_scb_free (struct ahc_softc*,struct scb*) ; 
 TYPE_2__ links ; 

__attribute__((used)) static __inline void
ahc_free_scb(struct ahc_softc *ahc, struct scb *scb)
{       
	struct hardware_scb *hscb;

	hscb = scb->hscb;
	/* Clean up for the next user */
	ahc->scb_data->scbindex[hscb->tag] = NULL;
	scb->flags = SCB_FLAG_NONE;
	hscb->control = 0;

	SLIST_INSERT_HEAD(&ahc->scb_data->free_scbs, scb, links.sle);

	/* Notify the OSM that a resource is now available. */
	aic_platform_scb_free(ahc, scb);
}