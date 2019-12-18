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
struct tty {int t_flags; unsigned int t_writepos; unsigned int t_column; int /*<<< orphan*/  t_outwait; int /*<<< orphan*/  t_inq; int /*<<< orphan*/  t_outq; } ;

/* Variables and functions */
 scalar_t__ CMP_FLAG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EIO ; 
 int ENXIO ; 
 int EWOULDBLOCK ; 
 int IO_NDELAY ; 
 int /*<<< orphan*/  MA_OWNED ; 
 unsigned int MIN (scalar_t__,int) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  OPOST ; 
 int TF_HIWAT_OUT ; 
 int TF_ZOMBIE ; 
 int TTY_STACKBUF ; 
 int /*<<< orphan*/  o ; 
 scalar_t__ tty_gone (struct tty*) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_lock_assert (struct tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int tty_wait (struct tty*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttydevsw_outwakeup (struct tty*) ; 
 unsigned int ttydisc_findchar (char*,unsigned int) ; 
 scalar_t__ ttydisc_write_oproc (struct tty*,char) ; 
 int /*<<< orphan*/  ttyinq_reprintpos_set (int /*<<< orphan*/ *) ; 
 unsigned int ttyoutq_write (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int uiomove (char*,unsigned int,struct uio*) ; 

int
ttydisc_write(struct tty *tp, struct uio *uio, int ioflag)
{
	char ob[TTY_STACKBUF];
	char *obstart;
	int error = 0;
	unsigned int oblen = 0;

	tty_lock_assert(tp, MA_OWNED);

	if (tp->t_flags & TF_ZOMBIE)
		return (EIO);

	/*
	 * We don't need to check whether the process is the foreground
	 * process group or if we have a carrier. This is already done
	 * in ttydev_write().
	 */

	while (uio->uio_resid > 0) {
		unsigned int nlen;

		MPASS(oblen == 0);

		/* Step 1: read data. */
		obstart = ob;
		nlen = MIN(uio->uio_resid, sizeof ob);
		tty_unlock(tp);
		error = uiomove(ob, nlen, uio);
		tty_lock(tp);
		if (error != 0)
			break;
		oblen = nlen;

		if (tty_gone(tp)) {
			error = ENXIO;
			break;
		}

		MPASS(oblen > 0);

		/* Step 2: process data. */
		do {
			unsigned int plen, wlen;

			/* Search for special characters for post processing. */
			if (CMP_FLAG(o, OPOST)) {
				plen = ttydisc_findchar(obstart, oblen);
			} else {
				plen = oblen;
			}

			if (plen == 0) {
				/*
				 * We're going to process a character
				 * that needs processing
				 */
				if (ttydisc_write_oproc(tp, *obstart) == 0) {
					obstart++;
					oblen--;

					tp->t_writepos = tp->t_column;
					ttyinq_reprintpos_set(&tp->t_inq);
					continue;
				}
			} else {
				/* We're going to write regular data. */
				wlen = ttyoutq_write(&tp->t_outq, obstart, plen);
				obstart += wlen;
				oblen -= wlen;
				tp->t_column += wlen;

				tp->t_writepos = tp->t_column;
				ttyinq_reprintpos_set(&tp->t_inq);

				if (wlen == plen)
					continue;
			}

			/* Watermark reached. Try to sleep. */
			tp->t_flags |= TF_HIWAT_OUT;

			if (ioflag & IO_NDELAY) {
				error = EWOULDBLOCK;
				goto done;
			}

			/*
			 * The driver may write back the data
			 * synchronously. Be sure to check the high
			 * water mark before going to sleep.
			 */
			ttydevsw_outwakeup(tp);
			if ((tp->t_flags & TF_HIWAT_OUT) == 0)
				continue;

			error = tty_wait(tp, &tp->t_outwait);
			if (error)
				goto done;

			if (tp->t_flags & TF_ZOMBIE) {
				error = EIO;
				goto done;
			}
		} while (oblen > 0);
	}

done:
	if (!tty_gone(tp))
		ttydevsw_outwakeup(tp);

	/*
	 * Add the amount of bytes that we didn't process back to the
	 * uio counters. We need to do this to make sure write() doesn't
	 * count the bytes we didn't store in the queue.
	 */
	uio->uio_resid += oblen;
	return (error);
}