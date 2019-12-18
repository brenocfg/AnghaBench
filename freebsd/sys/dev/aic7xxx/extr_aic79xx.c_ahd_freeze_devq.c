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
struct scb {int dummy; } ;
struct ahd_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAM_REQUEUE_REQ ; 
 int /*<<< orphan*/  ROLE_UNKNOWN ; 
 char SCB_GET_CHANNEL (struct ahd_softc*,struct scb*) ; 
 int SCB_GET_LUN (struct scb*) ; 
 int SCB_GET_TARGET (struct ahd_softc*,struct scb*) ; 
 int /*<<< orphan*/  SCB_LIST_NULL ; 
 int /*<<< orphan*/  SEARCH_COMPLETE ; 
 int /*<<< orphan*/  ahd_platform_freeze_devq (struct ahd_softc*,struct scb*) ; 
 int /*<<< orphan*/  ahd_search_qinfifo (struct ahd_softc*,int,char,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ahd_freeze_devq(struct ahd_softc *ahd, struct scb *scb)
{
	int	target;
	char	channel;
	int	lun;

	target = SCB_GET_TARGET(ahd, scb);
	lun = SCB_GET_LUN(scb);
	channel = SCB_GET_CHANNEL(ahd, scb);
	
	ahd_search_qinfifo(ahd, target, channel, lun,
			   /*tag*/SCB_LIST_NULL, ROLE_UNKNOWN,
			   CAM_REQUEUE_REQ, SEARCH_COMPLETE);

	ahd_platform_freeze_devq(ahd, scb);
}