#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int z_id; scalar_t__ z_domidx; int /*<<< orphan*/  z_logfuid; } ;
typedef  TYPE_1__ zfs_fuid_t ;
struct TYPE_10__ {int z_domain_cnt; int /*<<< orphan*/  z_fuids; int /*<<< orphan*/  z_domain_table; } ;
typedef  TYPE_2__ zfs_fuid_info_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 TYPE_1__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_insert_tail (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_2__* zfs_fuid_info_alloc () ; 
 void* zfs_replay_fuid_domain_common (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfs_replay_fuid_ugid (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zfs_fuid_info_t *
zfs_replay_fuids(void *start, void **end, int idcnt, int domcnt, uint64_t uid,
    uint64_t gid)
{
	uint64_t *log_fuid = (uint64_t *)start;
	zfs_fuid_info_t *fuid_infop;
	int i;

	fuid_infop = zfs_fuid_info_alloc();
	fuid_infop->z_domain_cnt = domcnt;

	fuid_infop->z_domain_table =
	    kmem_zalloc(domcnt * sizeof (char **), KM_SLEEP);

	for (i = 0; i != idcnt; i++) {
		zfs_fuid_t *zfuid;

		zfuid = kmem_alloc(sizeof (zfs_fuid_t), KM_SLEEP);
		zfuid->z_logfuid = *log_fuid;
		zfuid->z_id = -1;
		zfuid->z_domidx = 0;
		list_insert_tail(&fuid_infop->z_fuids, zfuid);
		log_fuid++;
	}

	zfs_replay_fuid_ugid(fuid_infop, uid, gid);

	*end = zfs_replay_fuid_domain_common(fuid_infop, log_fuid, domcnt);
	return (fuid_infop);
}