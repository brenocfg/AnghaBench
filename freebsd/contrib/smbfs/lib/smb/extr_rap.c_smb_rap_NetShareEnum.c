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
struct smb_rap {int r_entries; } ;
struct smb_ctx {int dummy; } ;

/* Variables and functions */
 int smb_rap_create (int /*<<< orphan*/ ,char*,char*,struct smb_rap**) ; 
 int /*<<< orphan*/  smb_rap_done (struct smb_rap*) ; 
 int smb_rap_error (struct smb_rap*,int) ; 
 int smb_rap_getNparam (struct smb_rap*,long*) ; 
 int smb_rap_request (struct smb_rap*,struct smb_ctx*) ; 
 int /*<<< orphan*/  smb_rap_setNparam (struct smb_rap*,int) ; 
 int /*<<< orphan*/  smb_rap_setPparam (struct smb_rap*,void*) ; 

int
smb_rap_NetShareEnum(struct smb_ctx *ctx, int sLevel, void *pbBuffer,
	int cbBuffer, int *pcEntriesRead, int *pcTotalAvail)
{
	struct smb_rap *rap;
	long lval;
	int error;

	error = smb_rap_create(0, "WrLeh", "B13BWz", &rap);
	if (error)
		return error;
	smb_rap_setNparam(rap, sLevel);		/* W - sLevel */
	smb_rap_setPparam(rap, pbBuffer);	/* r - pbBuffer */
	smb_rap_setNparam(rap, cbBuffer);	/* L - cbBuffer */
	error = smb_rap_request(rap, ctx);
	if (error == 0) {
		*pcEntriesRead = rap->r_entries;
		error = smb_rap_getNparam(rap, &lval);
		*pcTotalAvail = lval;
	}
	error = smb_rap_error(rap, error);
	smb_rap_done(rap);
	return error;
}