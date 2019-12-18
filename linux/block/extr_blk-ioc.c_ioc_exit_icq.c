#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct io_cq {int flags; TYPE_2__* q; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* exit_icq ) (struct io_cq*) ;} ;
struct elevator_type {TYPE_3__ ops; } ;
struct TYPE_5__ {TYPE_1__* elevator; } ;
struct TYPE_4__ {struct elevator_type* type; } ;

/* Variables and functions */
 int ICQ_EXITED ; 
 int /*<<< orphan*/  stub1 (struct io_cq*) ; 

__attribute__((used)) static void ioc_exit_icq(struct io_cq *icq)
{
	struct elevator_type *et = icq->q->elevator->type;

	if (icq->flags & ICQ_EXITED)
		return;

	if (et->ops.exit_icq)
		et->ops.exit_icq(icq);

	icq->flags |= ICQ_EXITED;
}