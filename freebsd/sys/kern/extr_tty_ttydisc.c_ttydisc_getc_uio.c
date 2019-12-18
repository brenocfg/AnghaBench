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
struct tty {int t_flags; int /*<<< orphan*/  t_outq; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MIN (scalar_t__,int) ; 
 int TF_STOPPED ; 
 int TTY_STACKBUF ; 
 int /*<<< orphan*/  atomic_add_long (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  getc_capture ; 
 int /*<<< orphan*/  getc_inject ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_lock_assert (struct tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_nout ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 size_t ttydisc_getc (struct tty*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttydisc_wakeup_watermark (struct tty*) ; 
 scalar_t__ ttyhook_hashook (struct tty*,int /*<<< orphan*/ ) ; 
 int ttyoutq_read_uio (int /*<<< orphan*/ *,struct tty*,struct uio*) ; 
 int uiomove (char*,size_t,struct uio*) ; 

int
ttydisc_getc_uio(struct tty *tp, struct uio *uio)
{
	int error = 0;
	ssize_t obytes = uio->uio_resid;
	size_t len;
	char buf[TTY_STACKBUF];

	tty_lock_assert(tp, MA_OWNED);

	if (tp->t_flags & TF_STOPPED)
		return (0);

	/*
	 * When a TTY hook is attached, we cannot perform unbuffered
	 * copying to userspace. Just call ttydisc_getc() and
	 * temporarily store data in a shadow buffer.
	 */
	if (ttyhook_hashook(tp, getc_capture) ||
	    ttyhook_hashook(tp, getc_inject)) {
		while (uio->uio_resid > 0) {
			/* Read to shadow buffer. */
			len = ttydisc_getc(tp, buf,
			    MIN(uio->uio_resid, sizeof buf));
			if (len == 0)
				break;

			/* Copy to userspace. */
			tty_unlock(tp);
			error = uiomove(buf, len, uio);
			tty_lock(tp);

			if (error != 0)
				break;
		}
	} else {
		error = ttyoutq_read_uio(&tp->t_outq, tp, uio);

		ttydisc_wakeup_watermark(tp);
		atomic_add_long(&tty_nout, obytes - uio->uio_resid);
	}

	return (error);
}