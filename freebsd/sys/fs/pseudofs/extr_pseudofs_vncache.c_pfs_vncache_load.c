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
 int /*<<< orphan*/  EVENTHANDLER_PRI_ANY ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_PFSVNCACHE ; 
 int /*<<< orphan*/  hashinit (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int maxproc ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfs_exit ; 
 int /*<<< orphan*/  pfs_exit_tag ; 
 int /*<<< orphan*/  pfs_vncache_hash ; 
 int /*<<< orphan*/  pfs_vncache_hashtbl ; 
 int /*<<< orphan*/  pfs_vncache_mutex ; 
 int /*<<< orphan*/  process_exit ; 

void
pfs_vncache_load(void)
{

	mtx_init(&pfs_vncache_mutex, "pfs_vncache", NULL, MTX_DEF);
	pfs_vncache_hashtbl = hashinit(maxproc / 4, M_PFSVNCACHE, &pfs_vncache_hash);
	pfs_exit_tag = EVENTHANDLER_REGISTER(process_exit, pfs_exit, NULL,
	    EVENTHANDLER_PRI_ANY);
}