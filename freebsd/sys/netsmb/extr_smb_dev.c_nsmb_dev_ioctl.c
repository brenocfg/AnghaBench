#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct uio {int uio_iovcnt; int /*<<< orphan*/  uio_resid; struct thread* uio_td; int /*<<< orphan*/  uio_rw; int /*<<< orphan*/  uio_segflg; int /*<<< orphan*/  uio_offset; struct iovec* uio_iov; } ;
struct thread {int dummy; } ;
struct smbioc_t2rq {int dummy; } ;
struct smbioc_rw {int /*<<< orphan*/  ioc_cnt; int /*<<< orphan*/  ioc_fh; int /*<<< orphan*/  ioc_offset; int /*<<< orphan*/  ioc_base; } ;
struct smbioc_rq {int dummy; } ;
struct smbioc_ossn {int dummy; } ;
struct smbioc_oshare {int dummy; } ;
struct smbioc_lookup {int dummy; } ;
struct smbioc_flags {void* ioc_level; int ioc_mask; int ioc_flags; } ;
struct TYPE_3__ {int co_flags; } ;
struct smb_vc {TYPE_1__ obj; } ;
struct TYPE_4__ {int co_flags; } ;
struct smb_share {TYPE_2__ obj; } ;
struct smb_dev {struct smb_share* sd_share; void* sd_level; struct smb_vc* sd_vc; } ;
struct smb_cred {int dummy; } ;
struct iovec {int /*<<< orphan*/  iov_len; int /*<<< orphan*/  iov_base; } ;
struct cdev {int dummy; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int EINVAL ; 
 int EISCONN ; 
 int ENODEV ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  M_NSMBDEV ; 
 int /*<<< orphan*/  M_WAITOK ; 
#define  SMBIOC_LOOKUP 135 
#define  SMBIOC_OPENSESSION 134 
#define  SMBIOC_OPENSHARE 133 
#define  SMBIOC_READ 132 
#define  SMBIOC_REQUEST 131 
#define  SMBIOC_SETFLAGS 130 
#define  SMBIOC_T2RQ 129 
#define  SMBIOC_WRITE 128 
 void* SMBL_SHARE ; 
 void* SMBL_VC ; 
 int SMBS_PERMANENT ; 
 int SMBV_PERMANENT ; 
 int /*<<< orphan*/  SMB_LOCK () ; 
 int /*<<< orphan*/  SMB_UNLOCK () ; 
 int /*<<< orphan*/  UIO_READ ; 
 int /*<<< orphan*/  UIO_USERSPACE ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 int devfs_get_cdevpriv (void**) ; 
 int /*<<< orphan*/  free (struct smb_cred*,int /*<<< orphan*/ ) ; 
 struct smb_cred* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_makescred (struct smb_cred*,struct thread*,int /*<<< orphan*/ *) ; 
 int smb_read (struct smb_share*,int /*<<< orphan*/ ,struct uio*,struct smb_cred*) ; 
 int smb_share_get (struct smb_share*,struct smb_cred*) ; 
 int /*<<< orphan*/  smb_share_put (struct smb_share*,struct smb_cred*) ; 
 int /*<<< orphan*/  smb_share_ref (struct smb_share*) ; 
 int /*<<< orphan*/  smb_share_rele (struct smb_share*,struct smb_cred*) ; 
 int /*<<< orphan*/  smb_share_unlock (struct smb_share*) ; 
 int smb_usr_lookup (struct smbioc_lookup*,struct smb_cred*,struct smb_vc**,struct smb_share**) ; 
 int smb_usr_opensession (struct smbioc_ossn*,struct smb_cred*,struct smb_vc**) ; 
 int smb_usr_openshare (struct smb_vc*,struct smbioc_oshare*,struct smb_cred*,struct smb_share**) ; 
 int smb_usr_simplerequest (struct smb_share*,struct smbioc_rq*,struct smb_cred*) ; 
 int smb_usr_t2request (struct smb_share*,struct smbioc_t2rq*,struct smb_cred*) ; 
 int smb_vc_get (struct smb_vc*,struct smb_cred*) ; 
 int /*<<< orphan*/  smb_vc_put (struct smb_vc*,struct smb_cred*) ; 
 int /*<<< orphan*/  smb_vc_ref (struct smb_vc*) ; 
 int /*<<< orphan*/  smb_vc_rele (struct smb_vc*,struct smb_cred*) ; 
 int /*<<< orphan*/  smb_vc_unlock (struct smb_vc*) ; 
 int smb_write (struct smb_share*,int /*<<< orphan*/ ,struct uio*,struct smb_cred*) ; 

__attribute__((used)) static int
nsmb_dev_ioctl(struct cdev *dev, u_long cmd, caddr_t data, int flag, struct thread *td)
{
	struct smb_dev *sdp;
	struct smb_vc *vcp;
	struct smb_share *ssp;
	struct smb_cred *scred;
	int error = 0;

	error = devfs_get_cdevpriv((void **)&sdp);
	if (error)
		return (error);
	scred = malloc(sizeof(struct smb_cred), M_NSMBDEV, M_WAITOK);
	SMB_LOCK();
	smb_makescred(scred, td, NULL);
	switch (cmd) {
	    case SMBIOC_OPENSESSION:
		if (sdp->sd_vc) {
			error = EISCONN;
			goto out;
		}
		error = smb_usr_opensession((struct smbioc_ossn*)data,
		    scred, &vcp);
		if (error)
			break;
		sdp->sd_vc = vcp;
		smb_vc_unlock(vcp);
		sdp->sd_level = SMBL_VC;
		break;
	    case SMBIOC_OPENSHARE:
		if (sdp->sd_share) {
			error = EISCONN;
			goto out;
		}
		if (sdp->sd_vc == NULL) {
			error = ENOTCONN;
			goto out;
		}
		error = smb_usr_openshare(sdp->sd_vc,
		    (struct smbioc_oshare*)data, scred, &ssp);
		if (error)
			break;
		sdp->sd_share = ssp;
		smb_share_unlock(ssp);
		sdp->sd_level = SMBL_SHARE;
		break;
	    case SMBIOC_REQUEST:
		if (sdp->sd_share == NULL) {
			error = ENOTCONN;
			goto out;
		}
		error = smb_usr_simplerequest(sdp->sd_share,
		    (struct smbioc_rq*)data, scred);
		break;
	    case SMBIOC_T2RQ:
		if (sdp->sd_share == NULL) {
			error = ENOTCONN;
			goto out;
		}
		error = smb_usr_t2request(sdp->sd_share,
		    (struct smbioc_t2rq*)data, scred);
		break;
	    case SMBIOC_SETFLAGS: {
		struct smbioc_flags *fl = (struct smbioc_flags*)data;
		int on;
	
		if (fl->ioc_level == SMBL_VC) {
			if (fl->ioc_mask & SMBV_PERMANENT) {
				on = fl->ioc_flags & SMBV_PERMANENT;
				if ((vcp = sdp->sd_vc) == NULL) {
					error = ENOTCONN;
					goto out;
				}
				error = smb_vc_get(vcp, scred);
				if (error)
					break;
				if (on && (vcp->obj.co_flags & SMBV_PERMANENT) == 0) {
					vcp->obj.co_flags |= SMBV_PERMANENT;
					smb_vc_ref(vcp);
				} else if (!on && (vcp->obj.co_flags & SMBV_PERMANENT)) {
					vcp->obj.co_flags &= ~SMBV_PERMANENT;
					smb_vc_rele(vcp, scred);
				}
				smb_vc_put(vcp, scred);
			} else
				error = EINVAL;
		} else if (fl->ioc_level == SMBL_SHARE) {
			if (fl->ioc_mask & SMBS_PERMANENT) {
				on = fl->ioc_flags & SMBS_PERMANENT;
				if ((ssp = sdp->sd_share) == NULL) {
					error = ENOTCONN;
					goto out;
				}
				error = smb_share_get(ssp, scred);
				if (error)
					break;
				if (on && (ssp->obj.co_flags & SMBS_PERMANENT) == 0) {
					ssp->obj.co_flags |= SMBS_PERMANENT;
					smb_share_ref(ssp);
				} else if (!on && (ssp->obj.co_flags & SMBS_PERMANENT)) {
					ssp->obj.co_flags &= ~SMBS_PERMANENT;
					smb_share_rele(ssp, scred);
				}
				smb_share_put(ssp, scred);
			} else
				error = EINVAL;
			break;
		} else
			error = EINVAL;
		break;
	    }
	    case SMBIOC_LOOKUP:
		if (sdp->sd_vc || sdp->sd_share) {
			error = EISCONN;
			goto out;
		}
		vcp = NULL;
		ssp = NULL;
		error = smb_usr_lookup((struct smbioc_lookup*)data, scred, &vcp, &ssp);
		if (error)
			break;
		if (vcp) {
			sdp->sd_vc = vcp;
			smb_vc_unlock(vcp);
			sdp->sd_level = SMBL_VC;
		}
		if (ssp) {
			sdp->sd_share = ssp;
			smb_share_unlock(ssp);
			sdp->sd_level = SMBL_SHARE;
		}
		break;
	    case SMBIOC_READ: case SMBIOC_WRITE: {
		struct smbioc_rw *rwrq = (struct smbioc_rw*)data;
		struct uio auio;
		struct iovec iov;
	
		if ((ssp = sdp->sd_share) == NULL) {
			error = ENOTCONN;
			goto out;
	 	}
		iov.iov_base = rwrq->ioc_base;
		iov.iov_len = rwrq->ioc_cnt;
		auio.uio_iov = &iov;
		auio.uio_iovcnt = 1;
		auio.uio_offset = rwrq->ioc_offset;
		auio.uio_resid = rwrq->ioc_cnt;
		auio.uio_segflg = UIO_USERSPACE;
		auio.uio_rw = (cmd == SMBIOC_READ) ? UIO_READ : UIO_WRITE;
		auio.uio_td = td;
		if (cmd == SMBIOC_READ)
			error = smb_read(ssp, rwrq->ioc_fh, &auio, scred);
		else
			error = smb_write(ssp, rwrq->ioc_fh, &auio, scred);
		rwrq->ioc_cnt -= auio.uio_resid;
		break;
	    }
	    default:
		error = ENODEV;
	}
out:
	free(scred, M_NSMBDEV);
	SMB_UNLOCK();
	return error;
}