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
struct ahc_softc {int flags; TYPE_1__* scb_data; } ;
struct TYPE_2__ {int maxhscbs; } ;

/* Variables and functions */
 int AHC_LSCBS_ENABLED ; 
 int AHC_PAGESCBS ; 
 scalar_t__ FREE_SCBH ; 
 scalar_t__ SCBPTR ; 
 scalar_t__ SCB_BASE ; 
 scalar_t__ SCB_CONTROL ; 
 int SCB_LIST_NULL ; 
 scalar_t__ SCB_LUN ; 
 scalar_t__ SCB_NEXT ; 
 scalar_t__ SCB_SCSIID ; 
 scalar_t__ SCB_TAG ; 
 int /*<<< orphan*/  ahc_outb (struct ahc_softc*,scalar_t__,int) ; 

__attribute__((used)) static void
ahc_build_free_scb_list(struct ahc_softc *ahc)
{
	int scbsize;
	int i;

	scbsize = 32;
	if ((ahc->flags & AHC_LSCBS_ENABLED) != 0)
		scbsize = 64;

	for (i = 0; i < ahc->scb_data->maxhscbs; i++) {
		int j;

		ahc_outb(ahc, SCBPTR, i);

		/*
		 * Touch all SCB bytes to avoid parity errors
		 * should one of our debugging routines read
		 * an otherwise uninitiatlized byte.
		 */
		for (j = 0; j < scbsize; j++)
			ahc_outb(ahc, SCB_BASE+j, 0xFF);

		/* Clear the control byte. */
		ahc_outb(ahc, SCB_CONTROL, 0);

		/* Set the next pointer */
		if ((ahc->flags & AHC_PAGESCBS) != 0)
			ahc_outb(ahc, SCB_NEXT, i+1);
		else 
			ahc_outb(ahc, SCB_NEXT, SCB_LIST_NULL);

		/* Make the tag number, SCSIID, and lun invalid */
		ahc_outb(ahc, SCB_TAG, SCB_LIST_NULL);
		ahc_outb(ahc, SCB_SCSIID, 0xFF);
		ahc_outb(ahc, SCB_LUN, 0xFF);
	}

	if ((ahc->flags & AHC_PAGESCBS) != 0) {
		/* SCB 0 heads the free list. */
		ahc_outb(ahc, FREE_SCBH, 0);
	} else {
		/* No free list. */
		ahc_outb(ahc, FREE_SCBH, SCB_LIST_NULL);
	}

	/* Make sure that the last SCB terminates the free list */
	ahc_outb(ahc, SCBPTR, i-1);
	ahc_outb(ahc, SCB_NEXT, SCB_LIST_NULL);
}