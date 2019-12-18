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
struct fsm {scalar_t__ proto; } ;
struct datalink {TYPE_1__* parent; } ;
struct TYPE_2__ {int /*<<< orphan*/  object; int /*<<< orphan*/  (* LayerStart ) (int /*<<< orphan*/ ,struct fsm*) ;} ;

/* Variables and functions */
 scalar_t__ PROTO_LCP ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct fsm*) ; 

__attribute__((used)) static void
datalink_LayerStart(void *v, struct fsm *fp)
{
  /* The given FSM is about to start up ! */
  struct datalink *dl = (struct datalink *)v;

  if (fp->proto == PROTO_LCP)
    (*dl->parent->LayerStart)(dl->parent->object, fp);
}