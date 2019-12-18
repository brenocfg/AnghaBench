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
typedef  int /*<<< orphan*/  u_short ;
struct link {int dummy; } ;
struct fsm_parent {int dummy; } ;
struct fsm_callbacks {int dummy; } ;
struct TYPE_4__ {char* name; } ;
struct TYPE_3__ {int reqs; int naks; int rejs; } ;
struct fsm {char const* name; int min_code; int max_code; int reqid; int restart; int LogLevel; TYPE_2__ StoppedTimer; TYPE_2__ OpenTimer; TYPE_2__ FsmTimer; struct fsm_callbacks* fn; struct fsm_parent const* parent; struct bundle* bundle; struct link* link; TYPE_1__ more; int /*<<< orphan*/  state; int /*<<< orphan*/  proto; } ;
struct bundle {int dummy; } ;

/* Variables and functions */
 int CODE_TERMACK ; 
 int /*<<< orphan*/  ST_INITIAL ; 
 int /*<<< orphan*/  ST_OPENED ; 
 int /*<<< orphan*/  memset (TYPE_2__*,char,int) ; 

void
fsm_Init(struct fsm *fp, const char *name, u_short proto, int mincode,
         int maxcode, int LogLevel, struct bundle *bundle,
         struct link *l, const struct fsm_parent *parent,
         struct fsm_callbacks *fn, const char * const timer_names[3])
{
  fp->name = name;
  fp->proto = proto;
  fp->min_code = mincode;
  fp->max_code = maxcode;
  fp->state = fp->min_code > CODE_TERMACK ? ST_OPENED : ST_INITIAL;
  fp->reqid = 1;
  fp->restart = 1;
  fp->more.reqs = fp->more.naks = fp->more.rejs = 3;
  memset(&fp->FsmTimer, '\0', sizeof fp->FsmTimer);
  memset(&fp->OpenTimer, '\0', sizeof fp->OpenTimer);
  memset(&fp->StoppedTimer, '\0', sizeof fp->StoppedTimer);
  fp->LogLevel = LogLevel;
  fp->link = l;
  fp->bundle = bundle;
  fp->parent = parent;
  fp->fn = fn;
  fp->FsmTimer.name = timer_names[0];
  fp->OpenTimer.name = timer_names[1];
  fp->StoppedTimer.name = timer_names[2];
}