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
struct jrefrec {scalar_t__ jr_op; scalar_t__ jr_ino; scalar_t__ jr_diroff; scalar_t__ jr_parent; scalar_t__ jr_nlink; } ;
struct jmvrec {scalar_t__ jm_op; scalar_t__ jm_oldoff; scalar_t__ jm_newoff; scalar_t__ jm_parent; scalar_t__ jm_ino; } ;
union jrec {struct jrefrec rec_jrefrec; struct jmvrec rec_jmvrec; } ;
typedef  int /*<<< orphan*/  uintmax_t ;
struct suj_rec {union jrec* sr_rec; } ;
struct suj_ino {int si_hasrecs; int /*<<< orphan*/  si_newrecs; } ;

/* Variables and functions */
 scalar_t__ JOP_ADDREF ; 
 scalar_t__ JOP_MVREF ; 
 scalar_t__ JOP_REMREF ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct suj_rec*,int /*<<< orphan*/ ) ; 
 scalar_t__ debug ; 
 struct suj_rec* errmalloc (int) ; 
 struct suj_ino* ino_lookup (scalar_t__,int) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  sr_next ; 

__attribute__((used)) static void
ino_append(union jrec *rec)
{
	struct jrefrec *refrec;
	struct jmvrec *mvrec;
	struct suj_ino *sino;
	struct suj_rec *srec;

	mvrec = &rec->rec_jmvrec;
	refrec = &rec->rec_jrefrec;
	if (debug && mvrec->jm_op == JOP_MVREF)
		printf("ino move: ino %ju, parent %ju, "
		    "diroff %jd, oldoff %jd\n",
		    (uintmax_t)mvrec->jm_ino, (uintmax_t)mvrec->jm_parent,
		    (uintmax_t)mvrec->jm_newoff, (uintmax_t)mvrec->jm_oldoff);
	else if (debug &&
	    (refrec->jr_op == JOP_ADDREF || refrec->jr_op == JOP_REMREF))
		printf("ino ref: op %d, ino %ju, nlink %ju, "
		    "parent %ju, diroff %jd\n",
		    refrec->jr_op, (uintmax_t)refrec->jr_ino,
		    (uintmax_t)refrec->jr_nlink,
		    (uintmax_t)refrec->jr_parent, (uintmax_t)refrec->jr_diroff);
	sino = ino_lookup(((struct jrefrec *)rec)->jr_ino, 1);
	sino->si_hasrecs = 1;
	srec = errmalloc(sizeof(*srec));
	srec->sr_rec = rec;
	TAILQ_INSERT_TAIL(&sino->si_newrecs, srec, sr_next);
}