#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  tv_sec; } ;
struct smbiod {int iod_sleeptimo; int /*<<< orphan*/  iod_evlock; int /*<<< orphan*/  iod_rqlock; scalar_t__ iod_id; int /*<<< orphan*/  iod_p; int /*<<< orphan*/  iod_evlist; int /*<<< orphan*/  iod_rqlist; int /*<<< orphan*/  iod_lastrqsent; TYPE_1__ iod_pingtimo; struct smb_vc* iod_vc; int /*<<< orphan*/  iod_state; } ;
struct smb_vc {struct smbiod* vc_iod; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_SMBIOD ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  RFNOWAIT ; 
 int /*<<< orphan*/  SMBERROR (char*,int) ; 
 int /*<<< orphan*/  SMBIOD_PING_TIMO ; 
 int SMBIOD_SLEEP_TIMO ; 
 int /*<<< orphan*/  SMBIOD_ST_NOTCONN ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct smbiod*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getnanotime (int /*<<< orphan*/ *) ; 
 int hz ; 
 int kproc_create (int /*<<< orphan*/ ,struct smbiod*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  smb_iod_next ; 
 int /*<<< orphan*/  smb_iod_thread ; 
 int /*<<< orphan*/  smb_sl_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smb_sl_init (int /*<<< orphan*/ *,char*) ; 
 struct smbiod* smb_zmalloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
smb_iod_create(struct smb_vc *vcp)
{
	struct smbiod *iod;
	int error;

	iod = smb_zmalloc(sizeof(*iod), M_SMBIOD, M_WAITOK);
	iod->iod_id = smb_iod_next++;
	iod->iod_state = SMBIOD_ST_NOTCONN;
	iod->iod_vc = vcp;
	iod->iod_sleeptimo = hz * SMBIOD_SLEEP_TIMO;
	iod->iod_pingtimo.tv_sec = SMBIOD_PING_TIMO;
	getnanotime(&iod->iod_lastrqsent);
	vcp->vc_iod = iod;
	smb_sl_init(&iod->iod_rqlock, "90rql");
	TAILQ_INIT(&iod->iod_rqlist);
	smb_sl_init(&iod->iod_evlock, "90evl");
	STAILQ_INIT(&iod->iod_evlist);
	error = kproc_create(smb_iod_thread, iod, &iod->iod_p,
	    RFNOWAIT, 0, "smbiod%d", iod->iod_id);
	if (error) {
		SMBERROR("can't start smbiod: %d", error);
		vcp->vc_iod = NULL;
		smb_sl_destroy(&iod->iod_rqlock);
		smb_sl_destroy(&iod->iod_evlock);
		free(iod, M_SMBIOD);
		return error;
	}
	return 0;
}