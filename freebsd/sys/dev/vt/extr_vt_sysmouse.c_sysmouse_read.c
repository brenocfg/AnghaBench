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
struct uio {unsigned int uio_resid; } ;
struct cdev {int dummy; } ;
typedef  unsigned int ssize_t ;

/* Variables and functions */
 int EWOULDBLOCK ; 
 unsigned int MOUSE_MSC_PACKETSIZE ; 
 unsigned int MOUSE_SYS_PACKETSIZE ; 
 int O_NONBLOCK ; 
 int cv_wait_sig (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int sysmouse_buf_read (struct uio*,unsigned int) ; 
 int sysmouse_level ; 
 int /*<<< orphan*/  sysmouse_lock ; 
 int /*<<< orphan*/  sysmouse_sleep ; 

__attribute__((used)) static int
sysmouse_read(struct cdev *dev, struct uio *uio, int ioflag)
{
	unsigned int length;
	ssize_t oresid;
	int error = 0;

	oresid = uio->uio_resid;

	mtx_lock(&sysmouse_lock);
	length = sysmouse_level >= 1 ? MOUSE_SYS_PACKETSIZE :
	    MOUSE_MSC_PACKETSIZE;

	while (uio->uio_resid >= length) {
		error = sysmouse_buf_read(uio, length);
		if (error == 0) {
			/* Process the next frame. */
			continue;
		} else if (error != EWOULDBLOCK) {
			/* Error (e.g. EFAULT). */
			break;
		} else {
			/* Block. */
			if (oresid != uio->uio_resid || ioflag & O_NONBLOCK)
				break;
			error = cv_wait_sig(&sysmouse_sleep, &sysmouse_lock);
			if (error != 0)
				break;
		}
	}
	mtx_unlock(&sysmouse_lock);

	return (error);
}