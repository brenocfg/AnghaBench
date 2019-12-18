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
struct scb {int dummy; } ;
struct ahc_softc {TYPE_1__* scb_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  sle; } ;
struct TYPE_3__ {int /*<<< orphan*/  free_scbs; } ;

/* Variables and functions */
 struct scb* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ahc_alloc_scbs (struct ahc_softc*) ; 
 TYPE_2__ links ; 

__attribute__((used)) static __inline struct scb *
ahc_get_scb(struct ahc_softc *ahc)
{
	struct scb *scb;

	if ((scb = SLIST_FIRST(&ahc->scb_data->free_scbs)) == NULL) {
		if (ahc_alloc_scbs(ahc) == 0)
			return (NULL);
		scb = SLIST_FIRST(&ahc->scb_data->free_scbs);
		if (scb == NULL)
			return (NULL);
	}
	SLIST_REMOVE_HEAD(&ahc->scb_data->free_scbs, links.sle);
	return (scb);
}