#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ my_prog; scalar_t__ my_proc; scalar_t__ my_vers; int /*<<< orphan*/  my_name; } ;
typedef  TYPE_1__ my_id ;
struct TYPE_9__ {TYPE_2__* monList; } ;
struct TYPE_8__ {scalar_t__ notifyProg; scalar_t__ notifyProc; scalar_t__ notifyVers; struct TYPE_8__* next; int /*<<< orphan*/  notifyHost; } ;
typedef  TYPE_2__ MonList ;
typedef  TYPE_3__ HostInfo ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  SM_MAXSTRLEN ; 
 int TRUE ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  strncasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_unmon(HostInfo *hp, my_id *idp)
{
  MonList *lp, *next;
  MonList *last = NULL;
  int result = FALSE;

  lp = hp->monList;
  while (lp)
  {
    if (!strncasecmp(idp->my_name, lp->notifyHost, SM_MAXSTRLEN)
      && (idp->my_prog == lp->notifyProg) && (idp->my_proc == lp->notifyProc)
      && (idp->my_vers == lp->notifyVers))
    {
      /* found one.  Unhook from chain and free.		*/
      next = lp->next;
      if (last) last->next = next;
      else hp->monList = next;
      free(lp);
      lp = next;
      result = TRUE;
    }
    else
    {
      last = lp;
      lp = lp->next;
    }
  }
  return (result);
}