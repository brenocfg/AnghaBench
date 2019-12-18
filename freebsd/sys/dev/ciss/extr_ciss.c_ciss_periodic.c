#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ciss_softc {scalar_t__ ciss_heartbeat; int ciss_heart_attack; int ciss_flags; int /*<<< orphan*/  ciss_periodic; TYPE_1__* ciss_cfg; } ;
struct ciss_request {int /*<<< orphan*/  cr_complete; struct ciss_command* cr_cc; } ;
struct TYPE_4__ {int cdb_length; int /*<<< orphan*/ * cdb; scalar_t__ timeout; int /*<<< orphan*/  direction; int /*<<< orphan*/  attribute; int /*<<< orphan*/  type; } ;
struct ciss_command {TYPE_2__ cdb; } ;
struct TYPE_3__ {scalar_t__ heartbeat; } ;

/* Variables and functions */
 int /*<<< orphan*/  CISS_CDB_ATTRIBUTE_SIMPLE ; 
 int /*<<< orphan*/  CISS_CDB_DIRECTION_WRITE ; 
 int /*<<< orphan*/  CISS_CDB_TYPE_MESSAGE ; 
 int CISS_FLAG_NOTIFY_OK ; 
 int CISS_HEARTBEAT_RATE ; 
 int /*<<< orphan*/  CISS_OPCODE_MESSAGE_NOP ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),struct ciss_softc*) ; 
 int /*<<< orphan*/  ciss_disable_adapter (struct ciss_softc*) ; 
 int ciss_get_request (struct ciss_softc*,struct ciss_request**) ; 
 int /*<<< orphan*/  ciss_nop_complete ; 
 scalar_t__ ciss_nop_message_heartbeat ; 
 int /*<<< orphan*/  ciss_notify_event (struct ciss_softc*) ; 
 int /*<<< orphan*/  ciss_printf (struct ciss_softc*,char*) ; 
 int ciss_start (struct ciss_request*) ; 
 int /*<<< orphan*/  debug (int,char*,...) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int hz ; 

__attribute__((used)) static void
ciss_periodic(void *arg)
{
    struct ciss_softc	*sc;
    struct ciss_request	*cr = NULL;
    struct ciss_command	*cc = NULL;
    int			error = 0;

    debug_called(1);

    sc = (struct ciss_softc *)arg;

    /*
     * Check the adapter heartbeat.
     */
    if (sc->ciss_cfg->heartbeat == sc->ciss_heartbeat) {
	sc->ciss_heart_attack++;
	debug(0, "adapter heart attack in progress 0x%x/%d",
	      sc->ciss_heartbeat, sc->ciss_heart_attack);
	if (sc->ciss_heart_attack == 3) {
	    ciss_printf(sc, "ADAPTER HEARTBEAT FAILED\n");
	    ciss_disable_adapter(sc);
	    return;
	}
    } else {
	sc->ciss_heartbeat = sc->ciss_cfg->heartbeat;
	sc->ciss_heart_attack = 0;
	debug(3, "new heartbeat 0x%x", sc->ciss_heartbeat);
    }

    /*
     * Send the NOP message and wait for a response.
     */
    if (ciss_nop_message_heartbeat != 0 && (error = ciss_get_request(sc, &cr)) == 0) {
	cc = cr->cr_cc;
	cr->cr_complete = ciss_nop_complete;
	cc->cdb.cdb_length = 1;
	cc->cdb.type = CISS_CDB_TYPE_MESSAGE;
	cc->cdb.attribute = CISS_CDB_ATTRIBUTE_SIMPLE;
	cc->cdb.direction = CISS_CDB_DIRECTION_WRITE;
	cc->cdb.timeout = 0;
	cc->cdb.cdb[0] = CISS_OPCODE_MESSAGE_NOP;

	if ((error = ciss_start(cr)) != 0) {
	    ciss_printf(sc, "SENDING NOP MESSAGE FAILED\n");
	}
    }

    /*
     * If the notify event request has died for some reason, or has
     * not started yet, restart it.
     */
    if (!(sc->ciss_flags & CISS_FLAG_NOTIFY_OK)) {
	debug(0, "(re)starting Event Notify chain");
	ciss_notify_event(sc);
    }

    /*
     * Reschedule.
     */
    callout_reset(&sc->ciss_periodic, CISS_HEARTBEAT_RATE * hz, ciss_periodic, sc);
}