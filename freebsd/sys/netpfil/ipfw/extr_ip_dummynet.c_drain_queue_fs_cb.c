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
struct TYPE_2__ {int flags; } ;
struct dn_fsk {int /*<<< orphan*/ * qht; int /*<<< orphan*/  drain_bucket; TYPE_1__ fs; } ;

/* Variables and functions */
 scalar_t__ DNHT_SCAN_DEL ; 
 int DN_QHT_HASH ; 
 int /*<<< orphan*/  dn_ht_scan_bucket (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__ (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ *),int /*<<< orphan*/ *) ; 
 scalar_t__ drain_queue_cb (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
drain_queue_fs_cb(void *_fs, void *arg)
{
	struct dn_fsk *fs = _fs;

	if (fs->fs.flags & DN_QHT_HASH) {
		/* Flowset has a hash table for queues */
		dn_ht_scan_bucket(fs->qht, &fs->drain_bucket,
				drain_queue_cb, NULL);
		fs->drain_bucket++;
	} else {
		/* No hash table for this flowset, null the pointer 
		 * if the queue is deleted
		 */
		if (fs->qht) {
			if (drain_queue_cb(fs->qht, NULL) == DNHT_SCAN_DEL)
				fs->qht = NULL;
		}
	}
	return 0;
}