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
struct tty {int dummy; } ;
struct snp_softc {struct tty* snp_tty; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ENXIO ; 
 int SNP_INPUT_BUFSIZE ; 
 int devfs_get_cdevpriv (void**) ; 
 int imin (scalar_t__,int) ; 
 scalar_t__ tty_gone (struct tty*) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int /*<<< orphan*/  ttydisc_rint_done (struct tty*) ; 
 int /*<<< orphan*/  ttydisc_rint_simple (struct tty*,char*,int) ; 
 int uiomove (char*,int,struct uio*) ; 

__attribute__((used)) static int
snp_write(struct cdev *dev, struct uio *uio, int flag)
{
	struct snp_softc *ss;
	struct tty *tp;
	int error, len;
	char in[SNP_INPUT_BUFSIZE];

	error = devfs_get_cdevpriv((void **)&ss);
	if (error != 0)
		return (error);

	tp = ss->snp_tty;
	if (tp == NULL || tty_gone(tp))
		return (EIO);

	while (uio->uio_resid > 0) {
		/* Read new data. */
		len = imin(uio->uio_resid, sizeof in);
		error = uiomove(in, len, uio);
		if (error != 0)
			return (error);

		tty_lock(tp);

		/* Driver could have abandoned the TTY in the mean time. */
		if (tty_gone(tp)) {
			tty_unlock(tp);
			return (ENXIO);
		}

		/*
		 * Deliver data to the TTY. Ignore errors for now,
		 * because we shouldn't bail out when we're running
		 * close to the watermarks.
		 */
		ttydisc_rint_simple(tp, in, len);
		ttydisc_rint_done(tp);

		tty_unlock(tp);
	}

	return (0);
}