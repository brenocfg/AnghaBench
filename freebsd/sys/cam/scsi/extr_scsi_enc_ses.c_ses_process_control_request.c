#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  union ccb {int dummy; } ccb ;
typedef  int /*<<< orphan*/  uint8_t ;
struct enc_fsm_state {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  ses_pending_requests; } ;
typedef  TYPE_1__ ses_softc_t ;
struct TYPE_6__ {TYPE_1__* enc_private; } ;
typedef  TYPE_2__ enc_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ses_poll_status (TYPE_2__*) ; 
 int /*<<< orphan*/  ses_terminate_control_requests (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ses_process_control_request(enc_softc_t *enc, struct enc_fsm_state *state,
    union ccb *ccb, uint8_t **bufp, int error, int xfer_len)
{
	ses_softc_t *ses;

	ses = enc->enc_private;
	/*
	 * Possible errors:
	 *  o Generation count wrong.
	 *  o Some SCSI status error.
	 */
	ses_terminate_control_requests(&ses->ses_pending_requests, error);
	ses_poll_status(enc);
	return (0);
}