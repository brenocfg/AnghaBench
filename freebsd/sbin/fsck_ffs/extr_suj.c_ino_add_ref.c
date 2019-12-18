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
struct suj_rec {scalar_t__ sr_rec; } ;
struct suj_ino {int /*<<< orphan*/  si_recs; } ;
struct jrefrec {scalar_t__ jr_parent; scalar_t__ jr_diroff; scalar_t__ jr_op; int /*<<< orphan*/  jr_nlink; int /*<<< orphan*/  jr_mode; } ;

/* Variables and functions */
 scalar_t__ JOP_ADDREF ; 
 scalar_t__ JOP_REMREF ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct suj_rec*,int /*<<< orphan*/ ) ; 
 struct suj_rec* TAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct suj_rec* TAILQ_PREV (struct suj_rec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sr_next ; 
 int /*<<< orphan*/  srechd ; 

__attribute__((used)) static void
ino_add_ref(struct suj_ino *sino, struct suj_rec *srec)
{
	struct jrefrec *refrec;
	struct suj_rec *srn;
	struct jrefrec *rrn;

	refrec = (struct jrefrec *)srec->sr_rec;
	/*
	 * We walk backwards so that the oldest link count is preserved.  If
	 * an add record conflicts with a remove keep the remove.  Redundant
	 * removes are eliminated in ino_build_ref.  Otherwise we keep the
	 * oldest record at a given location.
	 */
	for (srn = TAILQ_LAST(&sino->si_recs, srechd); srn;
	    srn = TAILQ_PREV(srn, srechd, sr_next)) {
		rrn = (struct jrefrec *)srn->sr_rec;
		if (rrn->jr_parent != refrec->jr_parent ||
		    rrn->jr_diroff != refrec->jr_diroff)
			continue;
		if (rrn->jr_op == JOP_REMREF || refrec->jr_op == JOP_ADDREF) {
			rrn->jr_mode = refrec->jr_mode;
			return;
		}
		/*
		 * Adding a remove.
		 *
		 * Replace the record in place with the old nlink in case
		 * we replace the head of the list.  Abandon srec as a dup.
		 */
		refrec->jr_nlink = rrn->jr_nlink;
		srn->sr_rec = srec->sr_rec;
		return;
	}
	TAILQ_INSERT_TAIL(&sino->si_recs, srec, sr_next);
}