#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int state; scalar_t__ restart; int /*<<< orphan*/  timer; } ;
struct cbcp {TYPE_2__* p; TYPE_1__ fsm; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {TYPE_3__* dl; } ;

/* Variables and functions */
#define  CBCP_ACKSENT 132 
#define  CBCP_CLOSED 131 
#define  CBCP_REQSENT 130 
#define  CBCP_RESPSENT 129 
#define  CBCP_STOPPED 128 
 int /*<<< orphan*/  LogCBCP ; 
 int /*<<< orphan*/  cbcp_SendAck (struct cbcp*) ; 
 int /*<<< orphan*/  cbcp_SendReq (struct cbcp*) ; 
 int /*<<< orphan*/  cbcp_SendResponse (struct cbcp*) ; 
 int /*<<< orphan*/  datalink_CBCPFailed (TYPE_3__*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  timer_Stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cbcp_Timeout(void *v)
{
  struct cbcp *cbcp = (struct cbcp *)v;

  timer_Stop(&cbcp->fsm.timer);
  if (cbcp->fsm.restart) {
    switch (cbcp->fsm.state) {
      case CBCP_CLOSED:
      case CBCP_STOPPED:
        log_Printf(LogCBCP, "%s: Urk - unexpected CBCP timeout !\n",
                   cbcp->p->dl->name);
        break;

      case CBCP_REQSENT:
        cbcp_SendReq(cbcp);
        break;
      case CBCP_RESPSENT:
        cbcp_SendResponse(cbcp);
        break;
      case CBCP_ACKSENT:
        cbcp_SendAck(cbcp);
        break;
    }
  } else {
    const char *missed;

    switch (cbcp->fsm.state) {
      case CBCP_STOPPED:
        missed = "REQ";
        break;
      case CBCP_REQSENT:
        missed = "RESPONSE";
        break;
      case CBCP_RESPSENT:
        missed = "ACK";
        break;
      case CBCP_ACKSENT:
        missed = "Terminate REQ";
        break;
      default:
        log_Printf(LogCBCP, "%s: Urk - unexpected CBCP timeout !\n",
                   cbcp->p->dl->name);
        missed = NULL;
        break;
    }
    if (missed)
      log_Printf(LogCBCP, "%s: Timeout waiting for peer %s\n",
                 cbcp->p->dl->name, missed);
    datalink_CBCPFailed(cbcp->p->dl);
  }
}