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
struct mount {int mnt_vfs_ops; int /*<<< orphan*/ * mnt_rootvnode; scalar_t__ mnt_ref; void* mnt_writeopcount_pcpu; void* mnt_lockref_pcpu; void* mnt_ref_pcpu; void* mnt_thread_in_ops_pcpu; int /*<<< orphan*/  mnt_explock; int /*<<< orphan*/  mnt_listmtx; int /*<<< orphan*/  mnt_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  PVFS ; 
 int /*<<< orphan*/  lockinit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcpu_zone_int ; 
 void* uma_zalloc_pcpu (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mount_init(void *mem, int size, int flags)
{
	struct mount *mp;

	mp = (struct mount *)mem;
	mtx_init(&mp->mnt_mtx, "struct mount mtx", NULL, MTX_DEF);
	mtx_init(&mp->mnt_listmtx, "struct mount vlist mtx", NULL, MTX_DEF);
	lockinit(&mp->mnt_explock, PVFS, "explock", 0, 0);
	mp->mnt_thread_in_ops_pcpu = uma_zalloc_pcpu(pcpu_zone_int,
	    M_WAITOK | M_ZERO);
	mp->mnt_ref_pcpu = uma_zalloc_pcpu(pcpu_zone_int,
	    M_WAITOK | M_ZERO);
	mp->mnt_lockref_pcpu = uma_zalloc_pcpu(pcpu_zone_int,
	    M_WAITOK | M_ZERO);
	mp->mnt_writeopcount_pcpu = uma_zalloc_pcpu(pcpu_zone_int,
	    M_WAITOK | M_ZERO);
	mp->mnt_ref = 0;
	mp->mnt_vfs_ops = 1;
	mp->mnt_rootvnode = NULL;
	return (0);
}