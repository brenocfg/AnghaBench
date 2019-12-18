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
struct suj_rec {TYPE_2__* sr_rec; } ;
struct suj_ino {scalar_t__ si_hasrecs; int /*<<< orphan*/  si_recs; int /*<<< orphan*/  si_movs; int /*<<< orphan*/  si_newrecs; } ;
struct TYPE_3__ {int jr_op; } ;
struct TYPE_4__ {TYPE_1__ rec_jrefrec; } ;

/* Variables and functions */
#define  JOP_ADDREF 130 
#define  JOP_MVREF 129 
#define  JOP_REMREF 128 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct suj_rec* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct suj_rec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct suj_rec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err_suj (char*,int) ; 
 int /*<<< orphan*/  ino_build_ref (struct suj_ino*,struct suj_rec*) ; 
 int /*<<< orphan*/  sr_next ; 

__attribute__((used)) static void
ino_build(struct suj_ino *sino)
{
	struct suj_rec *srec;

	while ((srec = TAILQ_FIRST(&sino->si_newrecs)) != NULL) {
		TAILQ_REMOVE(&sino->si_newrecs, srec, sr_next);
		switch (srec->sr_rec->rec_jrefrec.jr_op) {
		case JOP_ADDREF:
		case JOP_REMREF:
			ino_build_ref(sino, srec);
			break;
		case JOP_MVREF:
			/*
			 * Add this mvrec to the queue of pending mvs.
			 */
			TAILQ_INSERT_TAIL(&sino->si_movs, srec, sr_next);
			break;
		default:
			err_suj("ino_build: Unknown op %d\n",
			    srec->sr_rec->rec_jrefrec.jr_op);
		}
	}
	if (TAILQ_EMPTY(&sino->si_recs))
		sino->si_hasrecs = 0;
}