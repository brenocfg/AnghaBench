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
typedef  int /*<<< orphan*/  (* timer_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;
struct TYPE_3__ {scalar_t__ sival_int; } ;
struct TYPE_4__ {int /*<<< orphan*/  si_overrun; TYPE_1__ si_value; } ;
struct sigev_node {scalar_t__ sn_gen; TYPE_2__ sn_info; int /*<<< orphan*/  sn_value; int /*<<< orphan*/  (* sn_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */

__attribute__((used)) static void
timer_dispatch(struct sigev_node *sn)
{
	timer_func f = sn->sn_func;

	/* I want to avoid expired notification. */
	if (sn->sn_info.si_value.sival_int == sn->sn_gen)
		f(sn->sn_value, sn->sn_info.si_overrun);
}