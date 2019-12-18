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
typedef  int /*<<< orphan*/  u_int32_t ;
struct physical {int /*<<< orphan*/  async; TYPE_1__* handler; } ;
struct TYPE_2__ {void (* setasyncparams ) (struct physical*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  async_SetLinkParams (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void stub1 (struct physical*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
physical_SetAsyncParams(struct physical *p, u_int32_t mymap, u_int32_t hismap)
{
  if (p->handler && p->handler->setasyncparams)
    return (*p->handler->setasyncparams)(p, mymap, hismap);

  async_SetLinkParams(&p->async, mymap, hismap);
}