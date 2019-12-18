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
typedef  int uint32_t ;
struct scb {TYPE_1__* hscb; } ;
struct ahd_softc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sgptr; } ;

/* Variables and functions */
 int SG_STATUS_VALID ; 
 int /*<<< orphan*/  ahd_done (struct ahd_softc*,struct scb*) ; 
 int /*<<< orphan*/  ahd_handle_scb_status (struct ahd_softc*,struct scb*) ; 
 int aic_le32toh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
ahd_complete_scb(struct ahd_softc *ahd, struct scb *scb)
{
	uint32_t sgptr;

	sgptr = aic_le32toh(scb->hscb->sgptr);
	if ((sgptr & SG_STATUS_VALID) != 0)
		ahd_handle_scb_status(ahd, scb);
	else
		ahd_done(ahd, scb);
}