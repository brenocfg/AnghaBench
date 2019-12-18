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
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int MTX_DEF ; 
 int MTX_QUIET ; 
 int /*<<< orphan*/  ald_active ; 
 int /*<<< orphan*/  ald_mtx ; 
 int /*<<< orphan*/  ald_queues ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
ald_startup(void *unused)
{
	mtx_init(&ald_mtx, "ALDmtx", NULL, MTX_DEF|MTX_QUIET);
	LIST_INIT(&ald_queues);
	LIST_INIT(&ald_active);
}