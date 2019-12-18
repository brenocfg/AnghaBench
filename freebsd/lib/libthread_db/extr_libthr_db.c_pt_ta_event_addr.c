#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  thread_bp_death_addr; int /*<<< orphan*/  thread_bp_create_addr; } ;
typedef  TYPE_2__ td_thragent_t ;
struct TYPE_6__ {int /*<<< orphan*/  bptaddr; } ;
struct TYPE_8__ {TYPE_1__ u; void* type; } ;
typedef  TYPE_3__ td_notify_t ;
typedef  int td_event_e ;
typedef  int /*<<< orphan*/  td_err_e ;

/* Variables and functions */
 void* NOTIFY_BPT ; 
 int /*<<< orphan*/  TDBG_FUNC () ; 
#define  TD_CREATE 129 
#define  TD_DEATH 128 
 int /*<<< orphan*/  TD_ERR ; 

__attribute__((used)) static td_err_e
pt_ta_event_addr(const td_thragent_t *ta, td_event_e event, td_notify_t *ptr)
{

	TDBG_FUNC();

	switch (event) {
	case TD_CREATE:
		ptr->type = NOTIFY_BPT;
		ptr->u.bptaddr = ta->thread_bp_create_addr;
		return (0);
	case TD_DEATH:
		ptr->type = NOTIFY_BPT;
		ptr->u.bptaddr = ta->thread_bp_death_addr;
		return (0);
	default:
		return (TD_ERR);
	}
}