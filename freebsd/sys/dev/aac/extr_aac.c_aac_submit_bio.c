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
struct bio {TYPE_1__* bio_disk; } ;
struct aac_softc {int dummy; } ;
struct aac_disk {struct aac_softc* ad_controller; } ;
struct TYPE_2__ {scalar_t__ d_drv1; } ;

/* Variables and functions */
 char* HBA_FLAGS_DBG_FUNCTION_ENTRY_B ; 
 int /*<<< orphan*/  aac_enqueue_bio (struct aac_softc*,struct bio*) ; 
 int /*<<< orphan*/  aac_startio (struct aac_softc*) ; 
 int /*<<< orphan*/  fwprintf (struct aac_softc*,char*,char*) ; 

void
aac_submit_bio(struct bio *bp)
{
	struct aac_disk *ad;
	struct aac_softc *sc;

	ad = (struct aac_disk *)bp->bio_disk->d_drv1;
	sc = ad->ad_controller;
	fwprintf(sc, HBA_FLAGS_DBG_FUNCTION_ENTRY_B, "");

	/* queue the BIO and try to get some work done */
	aac_enqueue_bio(sc, bp);
	aac_startio(sc);
}