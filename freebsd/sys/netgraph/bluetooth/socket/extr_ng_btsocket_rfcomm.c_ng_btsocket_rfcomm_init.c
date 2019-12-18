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

/* Variables and functions */
 int /*<<< orphan*/  IS_DEFAULT_VNET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  NG_BTSOCKET_WARN_LEVEL ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curvnet ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_btsocket_rfcomm_debug_level ; 
 int /*<<< orphan*/  ng_btsocket_rfcomm_sessions ; 
 int /*<<< orphan*/  ng_btsocket_rfcomm_sessions_mtx ; 
 int /*<<< orphan*/  ng_btsocket_rfcomm_sessions_task ; 
 int /*<<< orphan*/  ng_btsocket_rfcomm_sockets ; 
 int /*<<< orphan*/  ng_btsocket_rfcomm_sockets_mtx ; 
 int /*<<< orphan*/  ng_btsocket_rfcomm_task ; 
 int ng_btsocket_rfcomm_timo ; 

void
ng_btsocket_rfcomm_init(void)
{

	/* Skip initialization of globals for non-default instances. */
	if (!IS_DEFAULT_VNET(curvnet))
		return;

	ng_btsocket_rfcomm_debug_level = NG_BTSOCKET_WARN_LEVEL;
	ng_btsocket_rfcomm_timo = 60;

	/* RFCOMM task */
	TASK_INIT(&ng_btsocket_rfcomm_task, 0,
		ng_btsocket_rfcomm_sessions_task, NULL);

	/* RFCOMM sessions list */
	LIST_INIT(&ng_btsocket_rfcomm_sessions);
	mtx_init(&ng_btsocket_rfcomm_sessions_mtx,
		"btsocks_rfcomm_sessions_mtx", NULL, MTX_DEF);

	/* RFCOMM sockets list */
	LIST_INIT(&ng_btsocket_rfcomm_sockets);
	mtx_init(&ng_btsocket_rfcomm_sockets_mtx,
		"btsocks_rfcomm_sockets_mtx", NULL, MTX_DEF);
}