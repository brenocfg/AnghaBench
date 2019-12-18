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
 int /*<<< orphan*/  MTX_DEF ; 
 int NOBJLISTS ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sw_alloc_sx ; 
 int /*<<< orphan*/  sw_dev_mtx ; 
 int /*<<< orphan*/ * swap_pager_object_list ; 
 int /*<<< orphan*/  swdev_syscall_lock ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
swap_pager_init(void)
{
	/*
	 * Initialize object lists
	 */
	int i;

	for (i = 0; i < NOBJLISTS; ++i)
		TAILQ_INIT(&swap_pager_object_list[i]);
	mtx_init(&sw_dev_mtx, "swapdev", NULL, MTX_DEF);
	sx_init(&sw_alloc_sx, "swspsx");
	sx_init(&swdev_syscall_lock, "swsysc");
}