#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct unpcb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_PRI_ANY ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_DEFAULT_VNET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TIMEOUT_TASK_INIT (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UMA_ALIGN_CACHE ; 
 int /*<<< orphan*/  UNP_DEFERRED_LOCK_INIT () ; 
 int /*<<< orphan*/  UNP_LINK_LOCK_INIT () ; 
 int /*<<< orphan*/  curvnet ; 
 int /*<<< orphan*/  maxsockets ; 
 int /*<<< orphan*/  maxsockets_change ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  taskqueue_thread ; 
 int /*<<< orphan*/ * uma_zcreate (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zone_set_max (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zone_set_warning (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  unp_defer_task ; 
 int /*<<< orphan*/  unp_defers ; 
 int /*<<< orphan*/  unp_dhead ; 
 int /*<<< orphan*/  unp_gc ; 
 int /*<<< orphan*/  unp_gc_task ; 
 int /*<<< orphan*/  unp_process_defers ; 
 int /*<<< orphan*/  unp_shead ; 
 int /*<<< orphan*/  unp_sphead ; 
 int /*<<< orphan*/ * unp_zone ; 
 int /*<<< orphan*/  unp_zone_change ; 

__attribute__((used)) static void
unp_init(void)
{

#ifdef VIMAGE
	if (!IS_DEFAULT_VNET(curvnet))
		return;
#endif
	unp_zone = uma_zcreate("unpcb", sizeof(struct unpcb), NULL, NULL,
	    NULL, NULL, UMA_ALIGN_CACHE, 0);
	if (unp_zone == NULL)
		panic("unp_init");
	uma_zone_set_max(unp_zone, maxsockets);
	uma_zone_set_warning(unp_zone, "kern.ipc.maxsockets limit reached");
	EVENTHANDLER_REGISTER(maxsockets_change, unp_zone_change,
	    NULL, EVENTHANDLER_PRI_ANY);
	LIST_INIT(&unp_dhead);
	LIST_INIT(&unp_shead);
	LIST_INIT(&unp_sphead);
	SLIST_INIT(&unp_defers);
	TIMEOUT_TASK_INIT(taskqueue_thread, &unp_gc_task, 0, unp_gc, NULL);
	TASK_INIT(&unp_defer_task, 0, unp_process_defers, NULL);
	UNP_LINK_LOCK_INIT();
	UNP_DEFERRED_LOCK_INIT();
}