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
struct scb {TYPE_1__* hscb; } ;
struct ahd_softc {int dummy; } ;
struct ahd_devinfo {int dummy; } ;
typedef  int /*<<< orphan*/  role_t ;
struct TYPE_2__ {int control; int /*<<< orphan*/  scsiid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ROLE_INITIATOR ; 
 int /*<<< orphan*/  ROLE_TARGET ; 
 int /*<<< orphan*/  SCB_GET_CHANNEL (struct ahd_softc*,struct scb*) ; 
 int /*<<< orphan*/  SCB_GET_LUN (struct scb*) ; 
 int /*<<< orphan*/  SCB_GET_TARGET (struct ahd_softc*,struct scb*) ; 
 int SCSIID_OUR_ID (int /*<<< orphan*/ ) ; 
 int TARGET_SCB ; 
 int /*<<< orphan*/  ahd_compile_devinfo (struct ahd_devinfo*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ahd_scb_devinfo(struct ahd_softc *ahd, struct ahd_devinfo *devinfo,
		struct scb *scb)
{
	role_t	role;
	int	our_id;

	our_id = SCSIID_OUR_ID(scb->hscb->scsiid);
	role = ROLE_INITIATOR;
	if ((scb->hscb->control & TARGET_SCB) != 0)
		role = ROLE_TARGET;
	ahd_compile_devinfo(devinfo, our_id, SCB_GET_TARGET(ahd, scb),
			    SCB_GET_LUN(scb), SCB_GET_CHANNEL(ahd, scb), role);
}