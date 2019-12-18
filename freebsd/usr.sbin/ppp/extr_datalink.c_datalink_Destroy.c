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
struct TYPE_2__ {int /*<<< orphan*/  timer; } ;
struct datalink {int state; struct datalink* name; int /*<<< orphan*/  physical; struct datalink* next; TYPE_1__ dial; int /*<<< orphan*/  chat; } ;

/* Variables and functions */
 int DATALINK_CLOSED ; 
#define  DATALINK_DIAL 130 
#define  DATALINK_HANGUP 129 
#define  DATALINK_LOGIN 128 
 int /*<<< orphan*/  LogERROR ; 
 int /*<<< orphan*/  chat_Destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  chat_Finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  datalink_State (struct datalink*) ; 
 int /*<<< orphan*/  free (struct datalink*) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  physical_Destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_Stop (int /*<<< orphan*/ *) ; 

struct datalink *
datalink_Destroy(struct datalink *dl)
{
  struct datalink *result;

  if (dl->state != DATALINK_CLOSED) {
    log_Printf(LogERROR, "Oops, destroying a datalink in state %s\n",
              datalink_State(dl));
    switch (dl->state) {
      case DATALINK_HANGUP:
      case DATALINK_DIAL:
      case DATALINK_LOGIN:
        chat_Finish(&dl->chat);		/* Gotta blat the timers ! */
        break;
    }
  }

  chat_Destroy(&dl->chat);
  timer_Stop(&dl->dial.timer);
  result = dl->next;
  physical_Destroy(dl->physical);
  free(dl->name);
  free(dl);

  return result;
}