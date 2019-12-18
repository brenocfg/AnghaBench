#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int flags; int /*<<< orphan*/  fs_nr; } ;
struct dn_fsk {scalar_t__ qht; TYPE_2__ fs; } ;
struct TYPE_3__ {int id; } ;
struct dn_fs {TYPE_1__ oid; } ;
struct copy_args {int /*<<< orphan*/  end; scalar_t__* start; } ;

/* Variables and functions */
 int DNHT_SCAN_END ; 
 int DN_QHT_HASH ; 
 int /*<<< orphan*/  ND (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ copy_obj (scalar_t__*,int /*<<< orphan*/ ,TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_q (struct copy_args*,struct dn_fsk*,int /*<<< orphan*/ ) ; 
 int dn_ht_entries (scalar_t__) ; 

__attribute__((used)) static int
copy_flowset(struct copy_args *a, struct dn_fsk *fs, int flags)
{
	struct dn_fs *ufs = (struct dn_fs *)(*a->start);
	if (!fs)
		return 0;
	ND("flowset %d", fs->fs.fs_nr);
	if (copy_obj(a->start, a->end, &fs->fs, "flowset", fs->fs.fs_nr))
		return DNHT_SCAN_END;
	ufs->oid.id = (fs->fs.flags & DN_QHT_HASH) ?
		dn_ht_entries(fs->qht) : (fs->qht ? 1 : 0);
	if (flags) {	/* copy queues */
		copy_q(a, fs, 0);
	}
	return 0;
}