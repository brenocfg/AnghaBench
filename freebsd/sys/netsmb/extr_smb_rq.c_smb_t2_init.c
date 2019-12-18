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
typedef  int /*<<< orphan*/  u_short ;
struct smb_t2rq {int t2_setupcount; int t2_fid; int /*<<< orphan*/  t2_vc; struct smb_cred* t2_cred; int /*<<< orphan*/ * t2_setup; int /*<<< orphan*/ * t2_setupdata; struct smb_connobj* t2_source; } ;
struct smb_cred {int dummy; } ;
struct smb_connobj {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct smb_t2rq*,int) ; 
 int smb_rq_getenv (struct smb_connobj*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
smb_t2_init(struct smb_t2rq *t2p, struct smb_connobj *source, u_short setup,
	struct smb_cred *scred)
{
	int error;

	bzero(t2p, sizeof(*t2p));
	t2p->t2_source = source;
	t2p->t2_setupcount = 1;
	t2p->t2_setupdata = t2p->t2_setup;
	t2p->t2_setup[0] = setup;
	t2p->t2_fid = 0xffff;
	t2p->t2_cred = scred;
	error = smb_rq_getenv(source, &t2p->t2_vc, NULL);
	if (error)
		return error;
	return 0;
}