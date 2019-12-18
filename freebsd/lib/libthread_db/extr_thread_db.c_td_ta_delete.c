#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* ta_ops; } ;
typedef  TYPE_2__ td_thragent_t ;
typedef  int /*<<< orphan*/  td_err_e ;
struct TYPE_6__ {int /*<<< orphan*/  (* to_ta_delete ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proclist ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  ta_next ; 

td_err_e
td_ta_delete(td_thragent_t *ta)
{
	TAILQ_REMOVE(&proclist, ta, ta_next);
	return (ta->ta_ops->to_ta_delete(ta));
}