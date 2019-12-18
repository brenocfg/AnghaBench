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
struct scb {int flags; } ;
struct ahc_softc {int /*<<< orphan*/  msg_type; scalar_t__ msgout_index; scalar_t__ msgout_len; } ;
struct ahc_devinfo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_TYPE_TARGET_MSGIN ; 
 int SCB_AUTO_NEGOTIATE ; 
 int /*<<< orphan*/  ahc_build_transfer_msg (struct ahc_softc*,struct ahc_devinfo*) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static void
ahc_setup_target_msgin(struct ahc_softc *ahc, struct ahc_devinfo *devinfo,
		       struct scb *scb)
{

	/*              
	 * To facilitate adding multiple messages together,
	 * each routine should increment the index and len
	 * variables instead of setting them explicitly.
	 */             
	ahc->msgout_index = 0;
	ahc->msgout_len = 0;

	if (scb != NULL && (scb->flags & SCB_AUTO_NEGOTIATE) != 0)
		ahc_build_transfer_msg(ahc, devinfo);
	else
		panic("ahc_intr: AWAITING target message with no message");

	ahc->msgout_index = 0;
	ahc->msg_type = MSG_TYPE_TARGET_MSGIN;
}