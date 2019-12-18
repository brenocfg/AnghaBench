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
struct mount {int /*<<< orphan*/  mnt_mtx; int /*<<< orphan*/  mnt_listmtx; int /*<<< orphan*/  mnt_explock; int /*<<< orphan*/  mnt_thread_in_ops_pcpu; int /*<<< orphan*/  mnt_ref_pcpu; int /*<<< orphan*/  mnt_lockref_pcpu; int /*<<< orphan*/  mnt_writeopcount_pcpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcpu_zone_int ; 
 int /*<<< orphan*/  uma_zfree_pcpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mount_fini(void *mem, int size)
{
	struct mount *mp;

	mp = (struct mount *)mem;
	uma_zfree_pcpu(pcpu_zone_int, mp->mnt_writeopcount_pcpu);
	uma_zfree_pcpu(pcpu_zone_int, mp->mnt_lockref_pcpu);
	uma_zfree_pcpu(pcpu_zone_int, mp->mnt_ref_pcpu);
	uma_zfree_pcpu(pcpu_zone_int, mp->mnt_thread_in_ops_pcpu);
	lockdestroy(&mp->mnt_explock);
	mtx_destroy(&mp->mnt_listmtx);
	mtx_destroy(&mp->mnt_mtx);
}