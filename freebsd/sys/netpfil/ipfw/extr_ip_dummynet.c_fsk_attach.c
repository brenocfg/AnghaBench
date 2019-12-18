#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; int /*<<< orphan*/  sched_nr; int /*<<< orphan*/  sched_mask; } ;
struct dn_schk {TYPE_2__ sch; TYPE_1__* fp; int /*<<< orphan*/  fsk_list; } ;
struct TYPE_7__ {int flags; int /*<<< orphan*/  fs_nr; int /*<<< orphan*/  flow_mask; } ;
struct dn_fsk {TYPE_3__ fs; int /*<<< orphan*/  fsk_mask; int /*<<< orphan*/ * qht; struct dn_schk* sched; } ;
struct TYPE_8__ {int /*<<< orphan*/  fsu; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* new_fsk ) (struct dn_fsk*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  D (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DN_HAVE_MASK ; 
 int DN_IS_RED ; 
 int DN_QHT_HASH ; 
 int /*<<< orphan*/  ND (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct dn_fsk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_REMOVE (int /*<<< orphan*/ *,struct dn_fsk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_red (struct dn_fsk*) ; 
 TYPE_4__ dn_cfg ; 
 int /*<<< orphan*/  dn_fsk ; 
 int /*<<< orphan*/  flow_id_or (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ nonzero_mask (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sch_chain ; 
 int /*<<< orphan*/  stub1 (struct dn_fsk*) ; 

__attribute__((used)) static void
fsk_attach(struct dn_fsk *fs, struct dn_schk *s)
{
	ND("remove fs %d from fsunlinked, link to sched %d",
		fs->fs.fs_nr, s->sch.sched_nr);
	SLIST_REMOVE(&dn_cfg.fsu, fs, dn_fsk, sch_chain);
	fs->sched = s;
	SLIST_INSERT_HEAD(&s->fsk_list, fs, sch_chain);
	if (s->fp->new_fsk)
		s->fp->new_fsk(fs);
	/* XXX compute fsk_mask */
	fs->fsk_mask = fs->fs.flow_mask;
	if (fs->sched->sch.flags & DN_HAVE_MASK)
		flow_id_or(&fs->sched->sch.sched_mask, &fs->fsk_mask);
	if (fs->qht) {
		/*
		 * we must drain qht according to the old
		 * type, and reinsert according to the new one.
		 * The requeue is complex -- in general we need to
		 * reclassify every single packet.
		 * For the time being, let's hope qht is never set
		 * when we reach this point.
		 */
		D("XXX TODO requeue from fs %d to sch %d",
			fs->fs.fs_nr, s->sch.sched_nr);
		fs->qht = NULL;
	}
	/* set the new type for qht */
	if (nonzero_mask(&fs->fsk_mask))
		fs->fs.flags |= DN_QHT_HASH;
	else
		fs->fs.flags &= ~DN_QHT_HASH;

	/* XXX config_red() can fail... */
	if (fs->fs.flags & DN_IS_RED)
		config_red(fs);
}