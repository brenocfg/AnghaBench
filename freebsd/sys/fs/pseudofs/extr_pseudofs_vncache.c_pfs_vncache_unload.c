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
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfs_exit_tag ; 
 int /*<<< orphan*/  pfs_purge_all () ; 
 scalar_t__ pfs_vncache_entries ; 
 int /*<<< orphan*/  pfs_vncache_mutex ; 
 int /*<<< orphan*/  process_exit ; 

void
pfs_vncache_unload(void)
{

	EVENTHANDLER_DEREGISTER(process_exit, pfs_exit_tag);
	pfs_purge_all();
	KASSERT(pfs_vncache_entries == 0,
	    ("%d vncache entries remaining", pfs_vncache_entries));
	mtx_destroy(&pfs_vncache_mutex);
}