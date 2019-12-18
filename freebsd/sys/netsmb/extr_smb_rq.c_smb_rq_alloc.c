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
typedef  int /*<<< orphan*/  u_char ;
struct smb_rq {int /*<<< orphan*/  sr_flags; } ;
struct smb_cred {int dummy; } ;
struct smb_connobj {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_SMBRQ ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  SMBR_ALLOCED ; 
 struct smb_rq* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_rq_done (struct smb_rq*) ; 
 int smb_rq_init (struct smb_rq*,struct smb_connobj*,int /*<<< orphan*/ ,struct smb_cred*) ; 

int
smb_rq_alloc(struct smb_connobj *layer, u_char cmd, struct smb_cred *scred,
	struct smb_rq **rqpp)
{
	struct smb_rq *rqp;
	int error;

	rqp = malloc(sizeof(*rqp), M_SMBRQ, M_WAITOK);
	if (rqp == NULL)
		return ENOMEM;
	error = smb_rq_init(rqp, layer, cmd, scred);
	rqp->sr_flags |= SMBR_ALLOCED;
	if (error) {
		smb_rq_done(rqp);
		return error;
	}
	*rqpp = rqp;
	return 0;
}