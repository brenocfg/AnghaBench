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
typedef  union jrec {int dummy; } jrec ;
struct suj_rec {union jrec* sr_rec; } ;
struct suj_ino {int dummy; } ;
struct jrefrec {int /*<<< orphan*/  jr_diroff; int /*<<< orphan*/  jr_op; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int /*<<< orphan*/  JOP_ADDREF ; 
 void* errmalloc (int) ; 
 int /*<<< orphan*/  ino_add_ref (struct suj_ino*,struct suj_rec*) ; 

__attribute__((used)) static void
ino_dup_ref(struct suj_ino *sino, struct jrefrec *refrec, off_t diroff)
{
	struct jrefrec *rrn;
	struct suj_rec *srn;

	rrn = errmalloc(sizeof(*refrec));
	*rrn = *refrec;
	rrn->jr_op = JOP_ADDREF;
	rrn->jr_diroff = diroff;
	srn = errmalloc(sizeof(*srn));
	srn->sr_rec = (union jrec *)rrn;
	ino_add_ref(sino, srn);
}