#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
union ccb {int /*<<< orphan*/  csio; int /*<<< orphan*/  ataio; } ;
typedef  int /*<<< orphan*/  uint8_t ;
struct enc_fsm_state {int /*<<< orphan*/  timeout; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  page_code; } ;
struct TYPE_3__ {scalar_t__ enc_type; } ;
typedef  TYPE_1__ enc_softc_t ;

/* Variables and functions */
 scalar_t__ ENC_SEMB_SES ; 
 int /*<<< orphan*/  MSG_SIMPLE_Q_TAG ; 
 int /*<<< orphan*/  SSD_FULL_SIZE ; 
 int /*<<< orphan*/  scsi_receive_diagnostic_results (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  semb_receive_diagnostic_results (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ses_fill_rcv_diag_io(enc_softc_t *enc, struct enc_fsm_state *state,
		       union ccb *ccb, uint8_t *buf)
{

	if (enc->enc_type == ENC_SEMB_SES) {
		semb_receive_diagnostic_results(&ccb->ataio, /*retries*/5,
					NULL, MSG_SIMPLE_Q_TAG, /*pcv*/1,
					state->page_code, buf, state->buf_size,
					state->timeout);
	} else {
		scsi_receive_diagnostic_results(&ccb->csio, /*retries*/5,
					NULL, MSG_SIMPLE_Q_TAG, /*pcv*/1,
					state->page_code, buf, state->buf_size,
					SSD_FULL_SIZE, state->timeout);
	}
	return (0);
}