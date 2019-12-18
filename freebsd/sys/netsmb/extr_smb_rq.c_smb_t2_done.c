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
struct smb_t2rq {int t2_flags; int /*<<< orphan*/  t2_rdata; int /*<<< orphan*/  t2_rparam; int /*<<< orphan*/  t2_tdata; int /*<<< orphan*/  t2_tparam; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_SMBRQ ; 
 int SMBT2_ALLOCED ; 
 int /*<<< orphan*/  free (struct smb_t2rq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_done (int /*<<< orphan*/ *) ; 

void
smb_t2_done(struct smb_t2rq *t2p)
{
	mb_done(&t2p->t2_tparam);
	mb_done(&t2p->t2_tdata);
	md_done(&t2p->t2_rparam);
	md_done(&t2p->t2_rdata);
	if (t2p->t2_flags & SMBT2_ALLOCED)
		free(t2p, M_SMBRQ);
}