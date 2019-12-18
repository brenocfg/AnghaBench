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
struct pvscsi_softc {int /*<<< orphan*/  free_list; int /*<<< orphan*/  lock; } ;
struct pvscsi_hcb {int /*<<< orphan*/  recovery; int /*<<< orphan*/ * e; int /*<<< orphan*/ * ccb; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PVSCSI_HCB_NONE ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct pvscsi_hcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pvscsi_hcb_put(struct pvscsi_softc *sc, struct pvscsi_hcb *hcb)
{

	mtx_assert(&sc->lock, MA_OWNED);
	hcb->ccb = NULL;
	hcb->e = NULL;
	hcb->recovery = PVSCSI_HCB_NONE;
	SLIST_INSERT_HEAD(&sc->free_list, hcb, links);
}