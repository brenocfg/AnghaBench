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
struct TYPE_2__ {int /*<<< orphan*/  speed; } ;
struct physical {TYPE_1__ cfg; int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogWARN ; 
 int /*<<< orphan*/  MODEM_SPEED ; 
 int PHYSICAL_FORCE_ASYNC ; 
 int PHYSICAL_FORCE_SYNC ; 
 int PHYSICAL_FORCE_SYNCNOACF ; 
 int PHYSICAL_NOFORCE ; 
 int /*<<< orphan*/  acflayer ; 
 int /*<<< orphan*/  asynclayer ; 
 int /*<<< orphan*/  ccplayer ; 
 int /*<<< orphan*/  hdlclayer ; 
 int /*<<< orphan*/  link_EmptyStack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link_Stack (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  lqrlayer ; 
 int /*<<< orphan*/  natlayer ; 
 scalar_t__ physical_IsSync (struct physical*) ; 
 int /*<<< orphan*/  physical_SetSync (struct physical*) ; 
 int /*<<< orphan*/  protolayer ; 
 int /*<<< orphan*/  synclayer ; 
 int /*<<< orphan*/  tcpmsslayer ; 
 int /*<<< orphan*/  vjlayer ; 

void
physical_SetupStack(struct physical *p, const char *who, int how)
{
  link_EmptyStack(&p->link);
  if (how == PHYSICAL_FORCE_SYNC || how == PHYSICAL_FORCE_SYNCNOACF ||
      (how == PHYSICAL_NOFORCE && physical_IsSync(p)))
    link_Stack(&p->link, &synclayer);
  else {
    link_Stack(&p->link, &asynclayer);
    link_Stack(&p->link, &hdlclayer);
  }
  if (how != PHYSICAL_FORCE_SYNCNOACF)
    link_Stack(&p->link, &acflayer);
  link_Stack(&p->link, &protolayer);
  link_Stack(&p->link, &lqrlayer);
  link_Stack(&p->link, &ccplayer);
  link_Stack(&p->link, &vjlayer);
  link_Stack(&p->link, &tcpmsslayer);
#ifndef NONAT
  link_Stack(&p->link, &natlayer);
#endif
  if (how == PHYSICAL_FORCE_ASYNC && physical_IsSync(p)) {
    log_Printf(LogWARN, "Sync device setting ignored for ``%s'' device\n", who);
    p->cfg.speed = MODEM_SPEED;
  } else if (how == PHYSICAL_FORCE_SYNC && !physical_IsSync(p)) {
    log_Printf(LogWARN, "Async device setting ignored for ``%s'' device\n",
               who);
    physical_SetSync(p);
  }
}