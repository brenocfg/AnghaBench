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
struct uio {int uio_resid; } ;
struct tty {int /*<<< orphan*/  t_mtx; } ;
struct snp_softc {int /*<<< orphan*/  snp_outwait; int /*<<< orphan*/  snp_outq; struct tty* snp_tty; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int EWOULDBLOCK ; 
 int O_NONBLOCK ; 
 int cv_wait_sig (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int devfs_get_cdevpriv (void**) ; 
 scalar_t__ tty_gone (struct tty*) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int ttyoutq_read_uio (int /*<<< orphan*/ *,struct tty*,struct uio*) ; 

__attribute__((used)) static int
snp_read(struct cdev *dev, struct uio *uio, int flag)
{
	int error, oresid = uio->uio_resid;
	struct snp_softc *ss;
	struct tty *tp;

	if (uio->uio_resid == 0)
		return (0);

	error = devfs_get_cdevpriv((void **)&ss);
	if (error != 0)
		return (error);

	tp = ss->snp_tty;
	if (tp == NULL || tty_gone(tp))
		return (EIO);

	tty_lock(tp);
	for (;;) {
		error = ttyoutq_read_uio(&ss->snp_outq, tp, uio);
		if (error != 0 || uio->uio_resid != oresid)
			break;

		/* Wait for more data. */
		if (flag & O_NONBLOCK) {
			error = EWOULDBLOCK;
			break;
		}
		error = cv_wait_sig(&ss->snp_outwait, tp->t_mtx);
		if (error != 0)
			break;
		if (tty_gone(tp)) {
			error = EIO;
			break;
		}
	}
	tty_unlock(tp);

	return (error);
}