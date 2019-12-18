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
struct smb_t2rq {int t2_flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int SMBR_RESTART ; 
 int SMBT2_NORESTART ; 
 int SMBT2_RESTART ; 
 int SMB_MAXRCN ; 
 int smb_t2_request_int (struct smb_t2rq*) ; 

int
smb_t2_request(struct smb_t2rq *t2p)
{
	int error = EINVAL, i;

	for (i = 0; i < SMB_MAXRCN; i++) {
		t2p->t2_flags &= ~SMBR_RESTART;
		error = smb_t2_request_int(t2p);
		if (error == 0)
			break;
		if ((t2p->t2_flags & (SMBT2_RESTART | SMBT2_NORESTART)) != SMBT2_RESTART)
			break;
	}
	return error;
}