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
struct smbiod_event {int ev_type; int ev_error; void* ev_ident; } ;
struct smbiod {int /*<<< orphan*/  iod_evlist; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_SMBIOD ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int PDROP ; 
 int PWAIT ; 
 int /*<<< orphan*/  SMBIODEBUG (char*) ; 
 int SMBIOD_EV_SYNC ; 
 int /*<<< orphan*/  SMB_IOD_EVLOCK (struct smbiod*) ; 
 int /*<<< orphan*/  SMB_IOD_EVLOCKPTR (struct smbiod*) ; 
 int /*<<< orphan*/  SMB_IOD_EVUNLOCK (struct smbiod*) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct smbiod_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_link ; 
 int /*<<< orphan*/  free (struct smbiod_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (struct smbiod_event*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_iod_wakeup (struct smbiod*) ; 
 struct smbiod_event* smb_zmalloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
smb_iod_request(struct smbiod *iod, int event, void *ident)
{
	struct smbiod_event *evp;
	int error;

	SMBIODEBUG("\n");
	evp = smb_zmalloc(sizeof(*evp), M_SMBIOD, M_WAITOK);
	evp->ev_type = event;
	evp->ev_ident = ident;
	SMB_IOD_EVLOCK(iod);
	STAILQ_INSERT_TAIL(&iod->iod_evlist, evp, ev_link);
	if ((event & SMBIOD_EV_SYNC) == 0) {
		SMB_IOD_EVUNLOCK(iod);
		smb_iod_wakeup(iod);
		return 0;
	}
	smb_iod_wakeup(iod);
	msleep(evp, SMB_IOD_EVLOCKPTR(iod), PWAIT | PDROP, "90evw", 0);
	error = evp->ev_error;
	free(evp, M_SMBIOD);
	return error;
}