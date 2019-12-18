#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  union ccb {int dummy; } ccb ;
typedef  int /*<<< orphan*/  uint8_t ;
struct scfg {scalar_t__ current_request_stage; scalar_t__ current_request_stages; TYPE_3__* current_request; } ;
struct enc_fsm_state {int dummy; } ;
struct TYPE_10__ {int result; int elm_idx; } ;
typedef  TYPE_3__ safte_control_request_t ;
struct TYPE_9__ {TYPE_1__* elm_map; } ;
struct TYPE_11__ {TYPE_2__ enc_cache; struct scfg* enc_private; } ;
typedef  TYPE_4__ enc_softc_t ;
struct TYPE_8__ {int elm_type; } ;

/* Variables and functions */
 int ELMTYP_ARRAY_DEV ; 
 int ELMTYP_DEVICE ; 
 int ENXIO ; 
 int /*<<< orphan*/  SAFTE_PROCESS_CONTROL_REQS ; 
 int /*<<< orphan*/  SAFTE_UPDATE_READENCSTATUS ; 
 int /*<<< orphan*/  SAFTE_UPDATE_READSLOTSTATUS ; 
 int SES_SETSTATUS_ENC_IDX ; 
 int /*<<< orphan*/  enc_update_request (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (TYPE_3__*) ; 

__attribute__((used)) static int
safte_process_control_request(enc_softc_t *enc, struct enc_fsm_state *state,
    union ccb *ccb, uint8_t **bufp, int error, int xfer_len)
{
	struct scfg *cfg;
	safte_control_request_t *req;
	int idx, type;

	cfg = enc->enc_private;
	if (cfg == NULL)
		return (ENXIO);

	req = cfg->current_request;
	if (req->result == 0)
		req->result = error;
	if (++cfg->current_request_stage >= cfg->current_request_stages) {
		idx = req->elm_idx;
		if (idx == SES_SETSTATUS_ENC_IDX)
			type = -1;
		else
			type = enc->enc_cache.elm_map[idx].elm_type;
		if (type == ELMTYP_DEVICE || type == ELMTYP_ARRAY_DEV)
			enc_update_request(enc, SAFTE_UPDATE_READSLOTSTATUS);
		else
			enc_update_request(enc, SAFTE_UPDATE_READENCSTATUS);
		cfg->current_request = NULL;
		wakeup(req);
	} else {
		enc_update_request(enc, SAFTE_PROCESS_CONTROL_REQS);
	}
	return (0);
}