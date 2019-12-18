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
struct datalink {scalar_t__ state; int /*<<< orphan*/  name; TYPE_1__* physical; struct datalink* next; } ;
struct TYPE_4__ {int /*<<< orphan*/  mp; } ;
struct bundle {TYPE_2__ ncp; struct datalink* links; } ;
struct TYPE_3__ {scalar_t__ type; } ;

/* Variables and functions */
 int AUTO_DOWN ; 
 int AUTO_UP ; 
 int /*<<< orphan*/  CLOSE_STAYDOWN ; 
 scalar_t__ DATALINK_CLOSED ; 
 scalar_t__ DATALINK_OPEN ; 
 int /*<<< orphan*/  LogPHASE ; 
 scalar_t__ PHYS_AUTO ; 
 int /*<<< orphan*/  datalink_Close (struct datalink*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  datalink_Up (struct datalink*,int,int) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_CheckAutoloadTimer (int /*<<< orphan*/ *) ; 

void
bundle_AutoAdjust(struct bundle *bundle, int percent, int what)
{
  struct datalink *dl, *choice, *otherlinkup;

  choice = otherlinkup = NULL;
  for (dl = bundle->links; dl; dl = dl->next)
    if (dl->physical->type == PHYS_AUTO) {
      if (dl->state == DATALINK_OPEN) {
        if (what == AUTO_DOWN) {
          if (choice)
            otherlinkup = choice;
          choice = dl;
        }
      } else if (dl->state == DATALINK_CLOSED) {
        if (what == AUTO_UP) {
          choice = dl;
          break;
        }
      } else {
        /* An auto link in an intermediate state - forget it for the moment */
        choice = NULL;
        break;
      }
    } else if (dl->state == DATALINK_OPEN && what == AUTO_DOWN)
      otherlinkup = dl;

  if (choice) {
    if (what == AUTO_UP) {
      log_Printf(LogPHASE, "%d%% saturation -> Opening link ``%s''\n",
                 percent, choice->name);
      datalink_Up(choice, 1, 1);
      mp_CheckAutoloadTimer(&bundle->ncp.mp);
    } else if (otherlinkup) {	/* Only bring the second-last link down */
      log_Printf(LogPHASE, "%d%% saturation -> Closing link ``%s''\n",
                 percent, choice->name);
      datalink_Close(choice, CLOSE_STAYDOWN);
      mp_CheckAutoloadTimer(&bundle->ncp.mp);
    }
  }
}