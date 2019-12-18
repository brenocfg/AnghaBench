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
struct TYPE_3__ {scalar_t__ sival_int; } ;
struct TYPE_4__ {TYPE_1__ si_value; } ;
struct sigev_node {scalar_t__ sn_gen; int /*<<< orphan*/  sn_value; TYPE_2__ sn_info; int /*<<< orphan*/  (* sn_func ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  (* mq_func ) (int /*<<< orphan*/ ) ;

/* Variables and functions */

__attribute__((used)) static void
mq_dispatch(struct sigev_node *sn)
{
	mq_func f = sn->sn_func;

	/*
	 * Check generation before calling user function,
	 * this should avoid expired notification.
	 */
	if (sn->sn_gen == sn->sn_info.si_value.sival_int)
		f(sn->sn_value);
}