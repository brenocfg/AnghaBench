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
union ccb {int /*<<< orphan*/  csio; int /*<<< orphan*/  ataio; } ;
typedef  int /*<<< orphan*/  uint8_t ;
struct enc_fsm_state {scalar_t__ page_code; int /*<<< orphan*/  timeout; int /*<<< orphan*/  buf_size; } ;
struct TYPE_5__ {scalar_t__ nelms; } ;
struct TYPE_6__ {scalar_t__ enc_type; TYPE_1__ enc_cache; } ;
typedef  TYPE_2__ enc_softc_t ;

/* Variables and functions */
 scalar_t__ ENC_SEMB_SAFT ; 
 int /*<<< orphan*/  MSG_SIMPLE_Q_TAG ; 
 scalar_t__ SAFTE_RD_RDCFG ; 
 int /*<<< orphan*/  SAFTE_UPDATE_READCONFIG ; 
 int /*<<< orphan*/  SSD_FULL_SIZE ; 
 int /*<<< orphan*/  enc_update_request (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_read_buffer (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  semb_read_buffer (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
safte_fill_read_buf_io(enc_softc_t *enc, struct enc_fsm_state *state,
		       union ccb *ccb, uint8_t *buf)
{

	if (state->page_code != SAFTE_RD_RDCFG &&
	    enc->enc_cache.nelms == 0) {
		enc_update_request(enc, SAFTE_UPDATE_READCONFIG);
		return (-1);
	}

	if (enc->enc_type == ENC_SEMB_SAFT) {
		semb_read_buffer(&ccb->ataio, /*retries*/5,
				NULL, MSG_SIMPLE_Q_TAG,
				state->page_code, buf, state->buf_size,
				state->timeout);
	} else {
		scsi_read_buffer(&ccb->csio, /*retries*/5,
				NULL, MSG_SIMPLE_Q_TAG, 1,
				state->page_code, 0, buf, state->buf_size,
				SSD_FULL_SIZE, state->timeout);
	}
	return (0);
}