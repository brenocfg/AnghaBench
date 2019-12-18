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
struct TYPE_4__ {int buckets; int /*<<< orphan*/  flags; int /*<<< orphan*/ * par; int /*<<< orphan*/  sched_nr; int /*<<< orphan*/  flow_mask; int /*<<< orphan*/  max_p; int /*<<< orphan*/  w_q; int /*<<< orphan*/  plr; int /*<<< orphan*/  qsize; int /*<<< orphan*/  fs_nr; } ;
struct dn_fsk {TYPE_2__ fs; int /*<<< orphan*/  min_th; int /*<<< orphan*/  max_th; } ;
struct TYPE_3__ {struct dn_flow_set* sle_next; } ;
struct dn_flow_set {int rq_elements; int rq_size; int /*<<< orphan*/  flags_fs; int /*<<< orphan*/  weight; int /*<<< orphan*/  parent_nr; int /*<<< orphan*/  flow_mask; int /*<<< orphan*/  max_p; int /*<<< orphan*/  min_th; int /*<<< orphan*/  max_th; int /*<<< orphan*/  w_q; int /*<<< orphan*/  plr; int /*<<< orphan*/  qsize; int /*<<< orphan*/  fs_nr; TYPE_1__ next; } ;
struct copy_args {int* start; } ;

/* Variables and functions */
 scalar_t__ DN_IS_QUEUE ; 
 int /*<<< orphan*/  convertflags2old (int /*<<< orphan*/ ) ; 

int
dn_c_copy_fs(struct dn_fsk *f, struct copy_args *a, int nq)
{
	struct dn_flow_set *fs = (struct dn_flow_set *)*a->start;

	fs->next.sle_next = (struct dn_flow_set *)DN_IS_QUEUE;
	fs->fs_nr = f->fs.fs_nr;
	fs->qsize = f->fs.qsize;
	fs->plr = f->fs.plr;
	fs->w_q = f->fs.w_q;
	fs->max_th = f->max_th;
	fs->min_th = f->min_th;
	fs->max_p = f->fs.max_p;
	fs->flow_mask = f->fs.flow_mask;
	fs->rq_elements = nq;
	fs->rq_size = (f->fs.buckets ? f->fs.buckets : 1);
	fs->parent_nr = f->fs.sched_nr;
	fs->weight = f->fs.par[0];

	fs->flags_fs = convertflags2old(f->fs.flags);
	*a->start += sizeof(struct dn_flow_set);
	return 0;
}