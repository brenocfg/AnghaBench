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
struct TYPE_4__ {TYPE_1__* parent_sq; } ;
struct throtl_grp {TYPE_2__ service_queue; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  nr_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  THROTL_TG_PENDING ; 
 int /*<<< orphan*/  tg_service_queue_add (struct throtl_grp*) ; 

__attribute__((used)) static void __throtl_enqueue_tg(struct throtl_grp *tg)
{
	tg_service_queue_add(tg);
	tg->flags |= THROTL_TG_PENDING;
	tg->service_queue.parent_sq->nr_pending++;
}