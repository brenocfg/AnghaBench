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
struct uio {scalar_t__ uio_resid; } ;
struct thread {int dummy; } ;
struct sf_hdtr {int /*<<< orphan*/  trl_cnt; int /*<<< orphan*/ * trailers; int /*<<< orphan*/  hdr_cnt; int /*<<< orphan*/ * headers; } ;
struct sendfile_args {scalar_t__ nbytes; int /*<<< orphan*/ * sbytes; int /*<<< orphan*/  flags; int /*<<< orphan*/  offset; int /*<<< orphan*/  s; int /*<<< orphan*/  fd; int /*<<< orphan*/ * hdtr; } ;
struct file {int dummy; } ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  hdtr ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_FD (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  M_IOV ; 
 int /*<<< orphan*/  cap_pread_rights ; 
 int copyin (int /*<<< orphan*/ *,struct sf_hdtr*,int) ; 
 int copyinuio (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct uio**) ; 
 int /*<<< orphan*/  copyout (scalar_t__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int fget_read (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct file**) ; 
 int fo_sendfile (struct file*,int /*<<< orphan*/ ,struct uio*,struct uio*,int /*<<< orphan*/ ,scalar_t__,scalar_t__*,int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  free (struct uio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sendfile(struct thread *td, struct sendfile_args *uap, int compat)
{
	struct sf_hdtr hdtr;
	struct uio *hdr_uio, *trl_uio;
	struct file *fp;
	off_t sbytes;
	int error;

	/*
	 * File offset must be positive.  If it goes beyond EOF
	 * we send only the header/trailer and no payload data.
	 */
	if (uap->offset < 0)
		return (EINVAL);

	sbytes = 0;
	hdr_uio = trl_uio = NULL;

	if (uap->hdtr != NULL) {
		error = copyin(uap->hdtr, &hdtr, sizeof(hdtr));
		if (error != 0)
			goto out;
		if (hdtr.headers != NULL) {
			error = copyinuio(hdtr.headers, hdtr.hdr_cnt,
			    &hdr_uio);
			if (error != 0)
				goto out;
#ifdef COMPAT_FREEBSD4
			/*
			 * In FreeBSD < 5.0 the nbytes to send also included
			 * the header.  If compat is specified subtract the
			 * header size from nbytes.
			 */
			if (compat) {
				if (uap->nbytes > hdr_uio->uio_resid)
					uap->nbytes -= hdr_uio->uio_resid;
				else
					uap->nbytes = 0;
			}
#endif
		}
		if (hdtr.trailers != NULL) {
			error = copyinuio(hdtr.trailers, hdtr.trl_cnt,
			    &trl_uio);
			if (error != 0)
				goto out;
		}
	}

	AUDIT_ARG_FD(uap->fd);

	/*
	 * sendfile(2) can start at any offset within a file so we require
	 * CAP_READ+CAP_SEEK = CAP_PREAD.
	 */
	if ((error = fget_read(td, uap->fd, &cap_pread_rights, &fp)) != 0)
		goto out;

	error = fo_sendfile(fp, uap->s, hdr_uio, trl_uio, uap->offset,
	    uap->nbytes, &sbytes, uap->flags, td);
	fdrop(fp, td);

	if (uap->sbytes != NULL)
		copyout(&sbytes, uap->sbytes, sizeof(off_t));

out:
	free(hdr_uio, M_IOV);
	free(trl_uio, M_IOV);
	return (error);
}