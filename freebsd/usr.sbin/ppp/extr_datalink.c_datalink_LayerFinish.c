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
struct fsm {scalar_t__ proto; scalar_t__ state; scalar_t__ open_mode; } ;
struct datalink {TYPE_1__* parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  object; int /*<<< orphan*/  (* LayerFinish ) (int /*<<< orphan*/ ,struct fsm*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CLOSE_NORMAL ; 
 scalar_t__ OPEN_PASSIVE ; 
 scalar_t__ PROTO_LCP ; 
 scalar_t__ ST_CLOSED ; 
 int /*<<< orphan*/  datalink_ComeDown (struct datalink*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsm2initial (struct fsm*) ; 
 int /*<<< orphan*/  fsm_Open (struct fsm*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct fsm*) ; 

__attribute__((used)) static void
datalink_LayerFinish(void *v, struct fsm *fp)
{
  /* The given fsm is now down */
  struct datalink *dl = (struct datalink *)v;

  if (fp->proto == PROTO_LCP) {
    fsm2initial(fp);
    (*dl->parent->LayerFinish)(dl->parent->object, fp);
    datalink_ComeDown(dl, CLOSE_NORMAL);
  } else if (fp->state == ST_CLOSED && fp->open_mode == OPEN_PASSIVE)
    fsm_Open(fp);		/* CCP goes to ST_STOPPED */
}