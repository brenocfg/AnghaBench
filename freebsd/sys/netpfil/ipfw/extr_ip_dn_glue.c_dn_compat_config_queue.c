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
struct dn_flow_set {int /*<<< orphan*/  max_p; int /*<<< orphan*/  min_th; int /*<<< orphan*/  max_th; int /*<<< orphan*/  w_q; int /*<<< orphan*/  flags_fs; int /*<<< orphan*/  weight; int /*<<< orphan*/  plr; int /*<<< orphan*/  qsize; int /*<<< orphan*/  rq_size; int /*<<< orphan*/  flow_mask; int /*<<< orphan*/  parent_nr; int /*<<< orphan*/  fs_nr; } ;
struct dn_pipe8 {struct dn_flow_set fs; } ;
struct dn_pipe7 {struct dn_flow_set fs; } ;
struct dn_fs {int flags; int /*<<< orphan*/  max_p; int /*<<< orphan*/  min_th; int /*<<< orphan*/  max_th; int /*<<< orphan*/  w_q; int /*<<< orphan*/ * par; int /*<<< orphan*/  plr; int /*<<< orphan*/  qsize; int /*<<< orphan*/  buckets; int /*<<< orphan*/  flow_mask; int /*<<< orphan*/  sched_nr; int /*<<< orphan*/  fs_nr; } ;

/* Variables and functions */
 int DN_IS_GENTLE_RED ; 
 int DN_IS_RED ; 
 int convertflags2new (int /*<<< orphan*/ ) ; 
 scalar_t__ is7 ; 

__attribute__((used)) static int
dn_compat_config_queue(struct dn_fs *fs, void* v)
{
	struct dn_pipe7 *p7 = (struct dn_pipe7 *)v;
	struct dn_pipe8 *p8 = (struct dn_pipe8 *)v;
	struct dn_flow_set *f;

	if (is7)
		f = &p7->fs;
	else
		f = &p8->fs;

	fs->fs_nr = f->fs_nr;
	fs->sched_nr = f->parent_nr;
	fs->flow_mask = f->flow_mask;
	fs->buckets = f->rq_size;
	fs->qsize = f->qsize;
	fs->plr = f->plr;
	fs->par[0] = f->weight;
	fs->flags = convertflags2new(f->flags_fs);
	if (fs->flags & DN_IS_GENTLE_RED || fs->flags & DN_IS_RED) {
		fs->w_q = f->w_q;
		fs->max_th = f->max_th;
		fs->min_th = f->min_th;
		fs->max_p = f->max_p;
	}

	return 0;
}