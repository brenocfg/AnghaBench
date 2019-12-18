#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dn_queue {int dummy; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  fs_nr; } ;
struct dn_fsk {int /*<<< orphan*/ * qht; TYPE_1__ fs; } ;

/* Variables and functions */
 int DN_DESTROY ; 
 int DN_QHT_HASH ; 
 int /*<<< orphan*/  ND (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dn_delete_queue (struct dn_queue*,int) ; 
 int /*<<< orphan*/  dn_ht_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dn_ht_scan (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  q_delete_cb ; 

__attribute__((used)) static void
qht_delete(struct dn_fsk *fs, int flags)
{
	ND("fs %d start flags %d qht %p",
		fs->fs.fs_nr, flags, fs->qht);
	if (!fs->qht)
		return;
	if (fs->fs.flags & DN_QHT_HASH) {
		dn_ht_scan(fs->qht, q_delete_cb, (void *)(uintptr_t)flags);
		if (flags & DN_DESTROY) {
			dn_ht_free(fs->qht, 0);
			fs->qht = NULL;
		}
	} else {
		dn_delete_queue((struct dn_queue *)(fs->qht), flags);
		if (flags & DN_DESTROY)
			fs->qht = NULL;
	}
}