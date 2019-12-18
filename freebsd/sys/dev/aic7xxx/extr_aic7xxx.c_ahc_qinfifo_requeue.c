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
struct scb {TYPE_3__* hscb; } ;
struct ahc_softc {TYPE_2__* next_queued_scb; int /*<<< orphan*/  qinfifonext; int /*<<< orphan*/ * qinfifo; } ;
struct TYPE_6__ {int /*<<< orphan*/  next; int /*<<< orphan*/  tag; } ;
struct TYPE_5__ {TYPE_1__* hscb; } ;
struct TYPE_4__ {int /*<<< orphan*/  tag; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  NEXT_QUEUED_SCB ; 
 int /*<<< orphan*/  ahc_outb (struct ahc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahc_sync_scb (struct ahc_softc*,struct scb*,int) ; 

__attribute__((used)) static void
ahc_qinfifo_requeue(struct ahc_softc *ahc, struct scb *prev_scb,
		    struct scb *scb)
{
	if (prev_scb == NULL) {
		ahc_outb(ahc, NEXT_QUEUED_SCB, scb->hscb->tag);
	} else {
		prev_scb->hscb->next = scb->hscb->tag;
		ahc_sync_scb(ahc, prev_scb, 
			     BUS_DMASYNC_PREREAD|BUS_DMASYNC_PREWRITE);
	}
	ahc->qinfifo[ahc->qinfifonext++] = scb->hscb->tag;
	scb->hscb->next = ahc->next_queued_scb->hscb->tag;
	ahc_sync_scb(ahc, scb, BUS_DMASYNC_PREREAD|BUS_DMASYNC_PREWRITE);
}