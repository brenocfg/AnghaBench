#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int run; int packetmode; } ;
struct TYPE_10__ {int /*<<< orphan*/  max; } ;
struct TYPE_8__ {int /*<<< orphan*/  max; } ;
struct TYPE_11__ {TYPE_4__ dial; TYPE_2__ reconnect; } ;
struct TYPE_9__ {int /*<<< orphan*/  tries; } ;
struct datalink {int state; TYPE_6__ script; TYPE_5__ cfg; TYPE_3__ dial; TYPE_1__* physical; int /*<<< orphan*/  reconnect_tries; int /*<<< orphan*/  bundle; } ;
struct TYPE_7__ {int type; } ;

/* Variables and functions */
 int DATALINK_CARRIER ; 
#define  DATALINK_CLOSED 132 
#define  DATALINK_DIAL 131 
#define  DATALINK_LOGIN 130 
#define  DATALINK_OPENING 129 
#define  DATALINK_READY 128 
 int /*<<< orphan*/  Enabled (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPT_FORCE_SCRIPTS ; 
 int /*<<< orphan*/  PHASE_DEAD ; 
 int /*<<< orphan*/  PHASE_ESTABLISH ; 
 int /*<<< orphan*/  PHASE_TERMINATE ; 
 int PHYS_DEDICATED ; 
 int PHYS_DIRECT ; 
 int /*<<< orphan*/  bundle_NewPhase (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bundle_Phase (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  datalink_NewState (struct datalink*,int) ; 

void
datalink_Up(struct datalink *dl, int runscripts, int packetmode)
{
  if (!Enabled(dl->bundle, OPT_FORCE_SCRIPTS) &&
      (dl->physical->type & (PHYS_DIRECT|PHYS_DEDICATED)))
    /* Ignore scripts */
    runscripts = 0;

  switch (dl->state) {
    case DATALINK_CLOSED:
      if (bundle_Phase(dl->bundle) == PHASE_DEAD ||
          bundle_Phase(dl->bundle) == PHASE_TERMINATE)
        bundle_NewPhase(dl->bundle, PHASE_ESTABLISH);
      datalink_NewState(dl, DATALINK_OPENING);
      dl->reconnect_tries =
        dl->physical->type == PHYS_DIRECT ? 0 : dl->cfg.reconnect.max;
      dl->dial.tries = dl->cfg.dial.max;
      dl->script.run = runscripts;
      dl->script.packetmode = packetmode;
      break;

    case DATALINK_OPENING:
      if (!dl->script.run && runscripts)
        dl->script.run = 1;
      /* FALLTHROUGH */

    case DATALINK_DIAL:
    case DATALINK_LOGIN:
    case DATALINK_READY:
      if (!dl->script.packetmode && packetmode) {
        dl->script.packetmode = 1;
        if (dl->state == DATALINK_READY) {
          dl->script.run = 0;
          datalink_NewState(dl, DATALINK_CARRIER);
        }
      }
      break;
  }
}