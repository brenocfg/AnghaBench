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
struct dn_fsk {scalar_t__ qht; TYPE_1__ fs; } ;
struct dn_flow_set {int dummy; } ;
struct dn_flow_queue8 {int dummy; } ;
struct copy_args {int end; int* start; } ;

/* Variables and functions */
 int /*<<< orphan*/  D (char*) ; 
 int DN_HAVE_MASK ; 
 int /*<<< orphan*/  dn_c_copy_fs (struct dn_fsk*,struct copy_args*,int) ; 
 int /*<<< orphan*/  dn_c_copy_q (scalar_t__,struct copy_args*) ; 
 int dn_ht_entries (scalar_t__) ; 
 int /*<<< orphan*/  dn_ht_scan (scalar_t__,int /*<<< orphan*/  (*) (scalar_t__,struct copy_args*),struct copy_args*) ; 

int
dn_compat_copy_queue(struct copy_args *a, void *_o)
{
	int have = a->end - *a->start;
	int need = 0;
	int fs_size = sizeof(struct dn_flow_set);
	int queue_size = sizeof(struct dn_flow_queue8);

	struct dn_fsk *fs = (struct dn_fsk *)_o;
	int n_queue = 0; /* number of queues */

	n_queue = (fs->fs.flags & DN_HAVE_MASK ? dn_ht_entries(fs->qht) :
						(fs->qht ? 1 : 0));

	need = fs_size + queue_size * n_queue;
	if (have < need) {
		D("have < need");
		return 1;
	}

	/* copy flowset */
	dn_c_copy_fs(fs, a, n_queue);

	/* copy queues */
	if (fs->fs.flags & DN_HAVE_MASK)
		dn_ht_scan(fs->qht, dn_c_copy_q, a);
	else if (fs->qht)
		dn_c_copy_q(fs->qht, a);

	return 0;
}