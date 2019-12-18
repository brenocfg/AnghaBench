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
struct dn_fsk_head {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  sched_nr; int /*<<< orphan*/  fs_nr; } ;
struct dn_fsk {TYPE_3__* sched; struct dn_fsk* w_q_lookup; TYPE_1__ fs; } ;
struct TYPE_8__ {struct dn_fsk_head fsu; int /*<<< orphan*/  fsk_count; } ;
struct TYPE_7__ {TYPE_2__* fp; struct dn_fsk_head fsk_list; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* free_fsk ) (struct dn_fsk*) ;} ;

/* Variables and functions */
 int DN_DELETE_FS ; 
 int DN_DESTROY ; 
 int DN_DETACH ; 
 int /*<<< orphan*/  M_DUMMYNET ; 
 int /*<<< orphan*/  ND (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (struct dn_fsk_head*,struct dn_fsk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_REMOVE (struct dn_fsk_head*,struct dn_fsk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aqm_cleanup_deconfig_fs (struct dn_fsk*) ; 
 int /*<<< orphan*/  bzero (struct dn_fsk*,int) ; 
 TYPE_4__ dn_cfg ; 
 int /*<<< orphan*/  dn_fsk ; 
 int /*<<< orphan*/  free (struct dn_fsk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qht_delete (struct dn_fsk*,int) ; 
 int /*<<< orphan*/  sch_chain ; 
 int /*<<< orphan*/  stub1 (struct dn_fsk*) ; 

__attribute__((used)) static void
fsk_detach(struct dn_fsk *fs, int flags)
{
	if (flags & DN_DELETE_FS)
		flags |= DN_DESTROY;
	ND("fs %d from sched %d flags %s %s %s",
		fs->fs.fs_nr, fs->fs.sched_nr,
		(flags & DN_DELETE_FS) ? "DEL_FS":"",
		(flags & DN_DESTROY) ? "DEL":"",
		(flags & DN_DETACH) ? "DET":"");
	if (flags & DN_DETACH) { /* detach from the list */
		struct dn_fsk_head *h;
		h = fs->sched ? &fs->sched->fsk_list : &dn_cfg.fsu;
		SLIST_REMOVE(h, fs, dn_fsk, sch_chain);
	}
	/* Free the RED parameters, they will be recomputed on
	 * subsequent attach if needed.
	 */
	if (fs->w_q_lookup)
		free(fs->w_q_lookup, M_DUMMYNET);
	fs->w_q_lookup = NULL;
	qht_delete(fs, flags);
#ifdef NEW_AQM
	aqm_cleanup_deconfig_fs(fs);
#endif

	if (fs->sched && fs->sched->fp->free_fsk)
		fs->sched->fp->free_fsk(fs);
	fs->sched = NULL;
	if (flags & DN_DELETE_FS) {
		bzero(fs, sizeof(*fs));	/* safety */
		free(fs, M_DUMMYNET);
		dn_cfg.fsk_count--;
	} else {
		SLIST_INSERT_HEAD(&dn_cfg.fsu, fs, sch_chain);
	}
}