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
typedef  int uint32_t ;
typedef  int u_long ;
struct tty {int dummy; } ;
struct thread {int /*<<< orphan*/  td_proc; } ;
struct snp_softc {int /*<<< orphan*/  snp_outq; struct tty* snp_tty; } ;
struct cdev {int dummy; } ;
typedef  void* dev_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int EBUSY ; 
 int ENOTTY ; 
#define  FIONREAD 131 
 void* NODEV ; 
#define  SNPGTTY 130 
#define  SNPGTYY_32DEV 129 
#define  SNPSTTY 128 
 int /*<<< orphan*/  SNP_LOCK () ; 
 int /*<<< orphan*/  SNP_OUTPUT_BUFSIZE ; 
 int /*<<< orphan*/  SNP_UNLOCK () ; 
 int devfs_get_cdevpriv (void**) ; 
 int /*<<< orphan*/  snp_hook ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 void* tty_udev (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int ttyhook_register (struct tty**,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,struct snp_softc*) ; 
 int ttyoutq_bytesused (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttyoutq_setsize (int /*<<< orphan*/ *,struct tty*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
snp_ioctl(struct cdev *dev, u_long cmd, caddr_t data, int flags,
    struct thread *td)
{
	struct snp_softc *ss;
	struct tty *tp;
	int error;

	error = devfs_get_cdevpriv((void **)&ss);
	if (error != 0)
		return (error);

	switch (cmd) {
	case SNPSTTY:
		/* Bind TTY to snoop instance. */
		SNP_LOCK();
		if (ss->snp_tty != NULL) {
			SNP_UNLOCK();
			return (EBUSY);
		}
		/*
		 * XXXRW / XXXJA: no capability check here.
		 */
		error = ttyhook_register(&ss->snp_tty, td->td_proc,
		    *(int *)data, &snp_hook, ss);
		SNP_UNLOCK();
		if (error != 0)
			return (error);

		/* Now that went okay, allocate a buffer for the queue. */
		tp = ss->snp_tty;
		tty_lock(tp);
		ttyoutq_setsize(&ss->snp_outq, tp, SNP_OUTPUT_BUFSIZE);
		tty_unlock(tp);

		return (0);
	case SNPGTTY:
		/* Obtain device number of associated TTY. */
		if (ss->snp_tty == NULL)
			*(dev_t *)data = NODEV;
		else
			*(dev_t *)data = tty_udev(ss->snp_tty);
		return (0);
	case SNPGTYY_32DEV:
		if (ss->snp_tty == NULL)
			*(uint32_t *)data = -1;
		else
			*(uint32_t *)data = tty_udev(ss->snp_tty); /* trunc */
		return (0);
	case FIONREAD:
		tp = ss->snp_tty;
		if (tp != NULL) {
			tty_lock(tp);
			*(int *)data = ttyoutq_bytesused(&ss->snp_outq);
			tty_unlock(tp);
		} else {
			*(int *)data = 0;
		}
		return (0);
	default:
		return (ENOTTY);
	}
}