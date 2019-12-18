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
typedef  int /*<<< orphan*/  uintmax_t ;
struct vnode {int dummy; } ;
struct vattr {int /*<<< orphan*/  va_gen; int /*<<< orphan*/  va_fileid; int /*<<< orphan*/  va_fsid; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
typedef  int fingerprint_status_t ;
typedef  int accmode_t ;

/* Variables and functions */
 int EAUTH ; 
 int EPERM ; 
#define  FINGERPRINT_FILE 130 
#define  FINGERPRINT_INDIRECT 129 
#define  FINGERPRINT_VALID 128 
 int /*<<< orphan*/  MAC_VERIEXEC_DBG (int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  VERIEXEC_FILES_FIRST ; 
 int VOP_GETATTR (struct vnode*,struct vattr*,struct ucred*) ; 
 int VVERIFY ; 
 int VWRITE ; 
 struct thread* curthread ; 
 int mac_veriexec_get_fingerprint_status (struct vnode*) ; 
 int mac_veriexec_metadata_fetch_fingerprint_status (struct vnode*,struct vattr*,struct thread*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mac_veriexec_check_vp(struct ucred *cred, struct vnode *vp, accmode_t accmode)
{
	struct vattr va;
	struct thread *td = curthread;
	fingerprint_status_t status;
	int error;

	/* Get vnode attributes */
	error = VOP_GETATTR(vp, &va, cred);
	if (error)
		return (error);

	/* Get the fingerprint status for the file */
	error = mac_veriexec_metadata_fetch_fingerprint_status(vp, &va, td,
	    VERIEXEC_FILES_FIRST);
	if (error && error != EAUTH)
		return (error);

	/*
	 * By now we should have status...
	 */
	status = mac_veriexec_get_fingerprint_status(vp);
	if (accmode & VWRITE) {
		/*
		 * If file has a fingerprint then deny the write request,
		 * otherwise invalidate the status so we don't keep checking
		 * for the file having a fingerprint. 
		 */
		switch (status) {
		case FINGERPRINT_FILE:
		case FINGERPRINT_VALID:
		case FINGERPRINT_INDIRECT:
			MAC_VERIEXEC_DBG(2,
			    "attempted write to fingerprinted file for dev "
			    "%ju, file %ju.%ju\n", (uintmax_t)va.va_fsid,
			    (uintmax_t)va.va_fileid, (uintmax_t)va.va_gen);
			return (EPERM);
		default:
			break;
		}
	}
	if (accmode & VVERIFY) {
		switch (status) {
		case FINGERPRINT_FILE:
		case FINGERPRINT_VALID:
		case FINGERPRINT_INDIRECT:
			if (error)
				return (error);
			break;
		default:
			/*
			 * Caller wants open to fail unless there is a valid
			 * fingerprint registered. 
			 */
			MAC_VERIEXEC_DBG(2, "fingerprint status is %d for dev "
			    "%ju, file %ju.%ju\n", status,
			    (uintmax_t)va.va_fsid, (uintmax_t)va.va_fileid,
			    (uintmax_t)va.va_gen);
			return (EAUTH);
		}
	}
	return (0);
}