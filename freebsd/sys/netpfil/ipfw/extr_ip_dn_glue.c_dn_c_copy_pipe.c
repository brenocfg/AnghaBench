#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int buckets; int /*<<< orphan*/  sched_mask; } ;
struct dn_link {int delay; void* link_nr; int /*<<< orphan*/  burst; int /*<<< orphan*/  bandwidth; } ;
struct dn_schk {TYPE_2__ sch; struct dn_profile* profile; struct dn_fsk* fs; struct dn_link link; } ;
struct dn_profile {int /*<<< orphan*/  samples_no; int /*<<< orphan*/  loss_level; int /*<<< orphan*/  name; } ;
struct dn_flow_set {int rq_size; int rq_elements; int /*<<< orphan*/  flags_fs; int /*<<< orphan*/  max_p; int /*<<< orphan*/  min_th; int /*<<< orphan*/  max_th; int /*<<< orphan*/  w_q; int /*<<< orphan*/  plr; int /*<<< orphan*/  qsize; void* parent_nr; int /*<<< orphan*/  flow_mask; } ;
struct dn_pipe8 {int /*<<< orphan*/  burst; int /*<<< orphan*/  samples_no; int /*<<< orphan*/  loss_level; int /*<<< orphan*/  name; struct dn_flow_set fs; } ;
struct TYPE_4__ {struct dn_pipe7* sle_next; } ;
struct dn_pipe7 {int delay; void* pipe_nr; int /*<<< orphan*/  bandwidth; TYPE_1__ next; struct dn_flow_set fs; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  max_p; int /*<<< orphan*/  w_q; int /*<<< orphan*/  plr; int /*<<< orphan*/  qsize; } ;
struct dn_fsk {TYPE_3__ fs; int /*<<< orphan*/  min_th; int /*<<< orphan*/  max_th; } ;
struct copy_args {int* start; } ;

/* Variables and functions */
 scalar_t__ DN_IS_PIPE ; 
 void* DN_MAX_ID ; 
 int /*<<< orphan*/  convertflags2old (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  div64 (int /*<<< orphan*/ ,int) ; 
 int hz ; 
 scalar_t__ is7 ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
dn_c_copy_pipe(struct dn_schk *s, struct copy_args *a, int nq)
{
	struct dn_link *l = &s->link;
	struct dn_fsk *f = s->fs;

	struct dn_pipe7 *pipe7 = (struct dn_pipe7 *)*a->start;
	struct dn_pipe8 *pipe8 = (struct dn_pipe8 *)*a->start;
	struct dn_flow_set *fs;
	int size = 0;

	if (is7) {
		fs = &pipe7->fs;
		size = sizeof(struct dn_pipe7);
	} else {
		fs = &pipe8->fs;
		size = sizeof(struct dn_pipe8);
	}

	/* These 4 field are the same in pipe7 and pipe8 */
	pipe7->next.sle_next = (struct dn_pipe7 *)DN_IS_PIPE;
	pipe7->bandwidth = l->bandwidth;
	pipe7->delay = l->delay * 1000 / hz;
	pipe7->pipe_nr = l->link_nr - DN_MAX_ID;

	if (!is7) {
		if (s->profile) {
			struct dn_profile *pf = s->profile;
			strncpy(pipe8->name, pf->name, sizeof(pf->name));
			pipe8->loss_level = pf->loss_level;
			pipe8->samples_no = pf->samples_no;
		}
		pipe8->burst = div64(l->burst , 8 * hz);
	}

	fs->flow_mask = s->sch.sched_mask;
	fs->rq_size = s->sch.buckets ? s->sch.buckets : 1;

	fs->parent_nr = l->link_nr - DN_MAX_ID;
	fs->qsize = f->fs.qsize;
	fs->plr = f->fs.plr;
	fs->w_q = f->fs.w_q;
	fs->max_th = f->max_th;
	fs->min_th = f->min_th;
	fs->max_p = f->fs.max_p;
	fs->rq_elements = nq;

	fs->flags_fs = convertflags2old(f->fs.flags);

	*a->start += size;
	return 0;
}