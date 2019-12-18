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
typedef  union ccb {int dummy; } ccb ;
struct targ_cdb_handlers {scalar_t__ cmd; int (* start ) (struct ccb_accept_tio*,struct ccb_scsiio*) ;int /*<<< orphan*/  (* done ) (struct ccb_accept_tio*,struct ccb_scsiio*,int /*<<< orphan*/ ) ;} ;
struct initiator_state {scalar_t__ pending_ca; scalar_t__ pending_ua; scalar_t__ orig_ua; scalar_t__ orig_ca; } ;
struct ccb_scsiio {scalar_t__ dxfer_len; int /*<<< orphan*/  init_id; } ;
struct TYPE_2__ {scalar_t__ targ_descr; int /*<<< orphan*/  flags; } ;
struct ccb_accept_tio {int /*<<< orphan*/  init_id; TYPE_1__ ccb_h; } ;
struct atio_descr {scalar_t__* cdb; int /*<<< orphan*/  init_req; } ;
typedef  int /*<<< orphan*/  io_ops ;

/* Variables and functions */
 int /*<<< orphan*/  ATIO_WORK ; 
 scalar_t__ CA_NONE ; 
 scalar_t__ CA_UNIT_ATTN ; 
 scalar_t__ ILLEGAL_CDB ; 
 scalar_t__ INQUIRY ; 
 int /*<<< orphan*/  SSD_KEY_UNIT_ATTENTION ; 
 scalar_t__ UA_NONE ; 
 scalar_t__ UA_POWER_ON ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  cdb_debug (scalar_t__*,char*,int /*<<< orphan*/ ) ; 
 struct targ_cdb_handlers* cdb_handlers ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  free_ccb (union ccb*) ; 
 int /*<<< orphan*/  send_ccb (union ccb*,int) ; 
 int /*<<< orphan*/  stub1 (struct ccb_accept_tio*,struct ccb_scsiio*,int /*<<< orphan*/ ) ; 
 int stub2 (struct ccb_accept_tio*,struct ccb_scsiio*) ; 
 struct initiator_state* tcmd_get_istate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcmd_illegal_req (struct ccb_accept_tio*,struct ccb_scsiio*) ; 
 int tcmd_rdwr (struct ccb_accept_tio*,struct ccb_scsiio*) ; 
 int /*<<< orphan*/  tcmd_sense (int /*<<< orphan*/ ,struct ccb_scsiio*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  warnx (char*,scalar_t__,...) ; 

int
tcmd_handle(struct ccb_accept_tio *atio, struct ccb_scsiio *ctio, io_ops event)
{
	static struct targ_cdb_handlers *last_cmd; 
	struct initiator_state *istate;
	struct atio_descr *a_descr;
	int ret;

	if (debug) {
		warnx("tcmd_handle atio %p ctio %p atioflags %#x", atio, ctio,
		      atio->ccb_h.flags);
	}
	ret = 0;
	a_descr = (struct atio_descr *)atio->ccb_h.targ_descr;

	/* Do a full lookup if one-behind cache failed */
	if (last_cmd == NULL || last_cmd->cmd != a_descr->cdb[0]) {
		struct targ_cdb_handlers *h; 

		for (h = cdb_handlers; h->cmd != ILLEGAL_CDB; h++) {
			if (a_descr->cdb[0] == h->cmd)
				break;
		}
		last_cmd = h;
	}

	/* call completion and exit */
	if (event != ATIO_WORK) {
		if (last_cmd->done != NULL)
			last_cmd->done(atio, ctio, event);
		else
			free_ccb((union ccb *)ctio);
		return (1);
	}

	if (last_cmd->cmd == ILLEGAL_CDB) {
		if (event != ATIO_WORK) {
			warnx("no done func for %#x???", a_descr->cdb[0]);
			abort();
		}
		/* Not found, return illegal request */
		warnx("cdb %#x not handled", a_descr->cdb[0]);
		tcmd_illegal_req(atio, ctio);
		send_ccb((union ccb *)ctio, /*priority*/1);
		return (0);
	}

	istate = tcmd_get_istate(ctio->init_id);
	if (istate == NULL) {
		tcmd_illegal_req(atio, ctio);
		send_ccb((union ccb *)ctio, /*priority*/1);
		return (0);
	}

	if (istate->pending_ca == 0 && istate->pending_ua != 0 &&
	    a_descr->cdb[0] != INQUIRY) {
		tcmd_sense(ctio->init_id, ctio, SSD_KEY_UNIT_ATTENTION,
			   0x29, istate->pending_ua == UA_POWER_ON ? 1 : 2);
		istate->pending_ca = CA_UNIT_ATTN;
		if (debug) {
			cdb_debug(a_descr->cdb, "UA active for %u: ",
				  atio->init_id);
		}
		send_ccb((union ccb *)ctio, /*priority*/1);
		return (0);
	} 

	/* Store current CA and UA for later */
	istate->orig_ua = istate->pending_ua;
	istate->orig_ca = istate->pending_ca;

	/*
	 * As per SAM2, any command that occurs
	 * after a CA is reported, clears the CA.  We must
	 * also clear the UA condition, if any, that caused
	 * the CA to occur assuming the UA is not for a
	 * persistent condition.
	 */
	istate->pending_ca = CA_NONE;
	if (istate->orig_ca == CA_UNIT_ATTN)
		istate->pending_ua = UA_NONE;

	/* If we have a valid handler, call start or completion function */
	if (last_cmd->cmd != ILLEGAL_CDB) {
		ret = last_cmd->start(atio, ctio);
		/* XXX hack */
		if (last_cmd->start != tcmd_rdwr) {
			a_descr->init_req += ctio->dxfer_len;
			send_ccb((union ccb *)ctio, /*priority*/1);
		}
	}

	return (ret);
}