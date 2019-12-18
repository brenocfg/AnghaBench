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
struct ipfw_flow_id {int dummy; } ;
struct TYPE_2__ {scalar_t__ subtype; } ;
struct dn_sch {int sched_nr; int flags; int /*<<< orphan*/  sched_mask; scalar_t__ buckets; TYPE_1__ oid; } ;
struct dn_pipe8 {int /*<<< orphan*/  burst; } ;
struct dn_pipe7 {int pipe_nr; int /*<<< orphan*/  delay; int /*<<< orphan*/  bandwidth; } ;
struct dn_link {int link_nr; int /*<<< orphan*/  burst; int /*<<< orphan*/  delay; int /*<<< orphan*/  bandwidth; } ;
struct dn_fs {int fs_nr; int sched_nr; int flags; int /*<<< orphan*/  flow_mask; scalar_t__ buckets; } ;

/* Variables and functions */
 int DN_HAVE_MASK ; 
 int DN_MAX_ID ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dn_compat_config_queue (struct dn_fs*,void*) ; 
 int /*<<< orphan*/  is7 ; 

__attribute__((used)) static int
dn_compat_config_pipe(struct dn_sch *sch, struct dn_link *p, 
		      struct dn_fs *fs, void* v)
{
	struct dn_pipe7 *p7 = (struct dn_pipe7 *)v;
	struct dn_pipe8 *p8 = (struct dn_pipe8 *)v;
	int i = p7->pipe_nr;

	sch->sched_nr = i;
	sch->oid.subtype = 0;
	p->link_nr = i;
	fs->fs_nr = i + 2*DN_MAX_ID;
	fs->sched_nr = i + DN_MAX_ID;

	/* Common to 7 and 8 */
	p->bandwidth = p7->bandwidth;
	p->delay = p7->delay;
	if (!is7) {
		/* FreeBSD 8 has burst  */
		p->burst = p8->burst;
	}

	/* fill the fifo flowset */
	dn_compat_config_queue(fs, v);
	fs->fs_nr = i + 2*DN_MAX_ID;
	fs->sched_nr = i + DN_MAX_ID;

	/* Move scheduler related parameter from fs to sch */
	sch->buckets = fs->buckets; /*XXX*/
	fs->buckets = 0;
	if (fs->flags & DN_HAVE_MASK) {
		sch->flags |= DN_HAVE_MASK;
		fs->flags &= ~DN_HAVE_MASK;
		sch->sched_mask = fs->flow_mask;
		bzero(&fs->flow_mask, sizeof(struct ipfw_flow_id));
	}

	return 0;
}