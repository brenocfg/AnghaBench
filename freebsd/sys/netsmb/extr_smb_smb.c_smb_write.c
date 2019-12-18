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
typedef  int /*<<< orphan*/  u_int16_t ;
struct uio {int uio_resid; } ;
struct smb_share {int dummy; } ;
struct smb_cred {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int smb_smb_write (struct smb_share*,int /*<<< orphan*/ ,int*,int*,struct uio*,struct smb_cred*) ; 

int
smb_write(struct smb_share *ssp, u_int16_t fid, struct uio *uio,
	struct smb_cred *scred)
{
	int error = 0, len, tsize, resid;
	struct uio olduio;

	tsize = uio->uio_resid;
	olduio = *uio;
	while (tsize > 0) {
		resid = 0;
		len = tsize;
		error = smb_smb_write(ssp, fid, &len, &resid, uio, scred);
		if (error)
			break;
		if (resid < len) {
			error = EIO;
			break;
		}
		tsize -= resid;
	}
	if (error) {
		/*
		 * Errors can happen on the copyin, the rpc, etc.  So they
		 * imply resid is unreliable.  The only safe thing is
		 * to pretend zero bytes made it.  We needn't restore the
		 * iovs because callers don't depend on them in error
		 * paths - uio_resid and uio_offset are what matter.
		 */
		*uio = olduio;
	}
	return error;
}