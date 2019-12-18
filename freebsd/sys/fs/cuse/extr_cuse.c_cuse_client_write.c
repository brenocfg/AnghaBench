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
struct uio {scalar_t__ uio_segflg; scalar_t__ uio_resid; TYPE_1__* uio_iov; } ;
struct cuse_client_command {int dummy; } ;
struct cuse_client {int /*<<< orphan*/  fflags; struct cuse_client_command* cmds; } ;
struct cdev {int dummy; } ;
struct TYPE_2__ {int iov_len; scalar_t__ iov_base; } ;

/* Variables and functions */
 size_t CUSE_CMD_WRITE ; 
 int CUSE_LENGTH_MAX ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EWOULDBLOCK ; 
 scalar_t__ UIO_NOCOPY ; 
 scalar_t__ UIO_USERSPACE ; 
 int cuse_client_get (struct cuse_client**) ; 
 int /*<<< orphan*/  cuse_client_kqfilter_poll (struct cdev*,struct cuse_client*) ; 
 int cuse_client_receive_command_locked (struct cuse_client_command*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cuse_client_send_command_locked (struct cuse_client_command*,uintptr_t,unsigned long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cuse_cmd_lock (struct cuse_client_command*) ; 
 int /*<<< orphan*/  cuse_cmd_unlock (struct cuse_client_command*) ; 
 int cuse_convert_error (int) ; 
 int /*<<< orphan*/  cuse_lock () ; 
 int /*<<< orphan*/  cuse_unlock () ; 
 int uiomove (int /*<<< orphan*/ *,int,struct uio*) ; 

__attribute__((used)) static int
cuse_client_write(struct cdev *dev, struct uio *uio, int ioflag)
{
	struct cuse_client_command *pccmd;
	struct cuse_client *pcc;
	int error;
	int len;

	error = cuse_client_get(&pcc);
	if (error != 0)
		return (error);

	pccmd = &pcc->cmds[CUSE_CMD_WRITE];

	if (uio->uio_segflg != UIO_USERSPACE) {
		return (EINVAL);
	}
	uio->uio_segflg = UIO_NOCOPY;

	cuse_cmd_lock(pccmd);

	while (uio->uio_resid != 0) {

		if (uio->uio_iov->iov_len > CUSE_LENGTH_MAX) {
			error = ENOMEM;
			break;
		}
		len = uio->uio_iov->iov_len;

		cuse_lock();
		cuse_client_send_command_locked(pccmd,
		    (uintptr_t)uio->uio_iov->iov_base,
		    (unsigned long)(unsigned int)len, pcc->fflags, ioflag);

		error = cuse_client_receive_command_locked(pccmd, 0, 0);
		cuse_unlock();

		if (error < 0) {
			error = cuse_convert_error(error);
			break;
		} else if (error == len) {
			error = uiomove(NULL, error, uio);
			if (error)
				break;
		} else {
			error = uiomove(NULL, error, uio);
			break;
		}
	}
	cuse_cmd_unlock(pccmd);

	uio->uio_segflg = UIO_USERSPACE;/* restore segment flag */

	if (error == EWOULDBLOCK)
		cuse_client_kqfilter_poll(dev, pcc);

	return (error);
}