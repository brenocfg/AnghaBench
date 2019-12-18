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
struct smb_t2rq {int /*<<< orphan*/  t2_flags; } ;
struct smb_cred {int dummy; } ;
struct smb_connobj {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_SMBRQ ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  SMBT2_ALLOCED ; 
 struct smb_t2rq* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_t2_done (struct smb_t2rq*) ; 
 int smb_t2_init (struct smb_t2rq*,struct smb_connobj*,int /*<<< orphan*/ ,struct smb_cred*) ; 

int
smb_t2_alloc(struct smb_connobj *layer, u_short setup, struct smb_cred *scred,
	struct smb_t2rq **t2pp)
{
	struct smb_t2rq *t2p;
	int error;

	t2p = malloc(sizeof(*t2p), M_SMBRQ, M_WAITOK);
	if (t2p == NULL)
		return ENOMEM;
	error = smb_t2_init(t2p, layer, setup, scred);
	t2p->t2_flags |= SMBT2_ALLOCED;
	if (error) {
		smb_t2_done(t2p);
		return error;
	}
	*t2pp = t2p;
	return 0;
}