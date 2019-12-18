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
typedef  int /*<<< orphan*/  u_int ;
struct uio {scalar_t__ uio_resid; } ;
struct cdev {int dummy; } ;
struct audit_pipe_entry {scalar_t__ ape_record_len; scalar_t__ ape_record; } ;
struct audit_pipe {int ap_flags; scalar_t__ ap_qoffset; int /*<<< orphan*/  ap_qlen; int /*<<< orphan*/  ap_qbyteslen; int /*<<< orphan*/  ap_queue; int /*<<< orphan*/  ap_reads; int /*<<< orphan*/  ap_cv; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_PIPE_LOCK (struct audit_pipe*) ; 
 int /*<<< orphan*/  AUDIT_PIPE_LOCK_ASSERT (struct audit_pipe*) ; 
 int /*<<< orphan*/  AUDIT_PIPE_MTX (struct audit_pipe*) ; 
 int AUDIT_PIPE_NBIO ; 
 scalar_t__ AUDIT_PIPE_SX_XLOCK_SIG (struct audit_pipe*) ; 
 int /*<<< orphan*/  AUDIT_PIPE_SX_XUNLOCK (struct audit_pipe*) ; 
 int /*<<< orphan*/  AUDIT_PIPE_UNLOCK (struct audit_pipe*) ; 
 int EAGAIN ; 
 int EINTR ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MIN (scalar_t__,scalar_t__) ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct audit_pipe_entry* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct audit_pipe_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ape_queue ; 
 int /*<<< orphan*/  audit_pipe_entry_free (struct audit_pipe_entry*) ; 
 int cv_wait_sig (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int devfs_get_cdevpriv (void**) ; 
 int uiomove (char*,int /*<<< orphan*/ ,struct uio*) ; 

__attribute__((used)) static int
audit_pipe_read(struct cdev *dev, struct uio *uio, int flag)
{
	struct audit_pipe_entry *ape;
	struct audit_pipe *ap;
	u_int toread;
	int error;

	error = devfs_get_cdevpriv((void **)&ap);
	if (error != 0)
		return (error);

	/*
	 * We hold an sx(9) lock over read and flush because we rely on the
	 * stability of a record in the queue during uiomove(9).
	 */
	if (AUDIT_PIPE_SX_XLOCK_SIG(ap) != 0)
		return (EINTR);
	AUDIT_PIPE_LOCK(ap);
	while (TAILQ_EMPTY(&ap->ap_queue)) {
		if (ap->ap_flags & AUDIT_PIPE_NBIO) {
			AUDIT_PIPE_UNLOCK(ap);
			AUDIT_PIPE_SX_XUNLOCK(ap);
			return (EAGAIN);
		}
		error = cv_wait_sig(&ap->ap_cv, AUDIT_PIPE_MTX(ap));
		if (error) {
			AUDIT_PIPE_UNLOCK(ap);
			AUDIT_PIPE_SX_XUNLOCK(ap);
			return (error);
		}
	}

	/*
	 * Copy as many remaining bytes from the current record to userspace
	 * as we can.  Keep processing records until we run out of records in
	 * the queue, or until the user buffer runs out of space.
	 *
	 * Note: we rely on the SX lock to maintain ape's stability here.
	 */
	ap->ap_reads++;
	while ((ape = TAILQ_FIRST(&ap->ap_queue)) != NULL &&
	    uio->uio_resid > 0) {
		AUDIT_PIPE_LOCK_ASSERT(ap);

		KASSERT(ape->ape_record_len > ap->ap_qoffset,
		    ("audit_pipe_read: record_len > qoffset (1)"));
		toread = MIN(ape->ape_record_len - ap->ap_qoffset,
		    uio->uio_resid);
		AUDIT_PIPE_UNLOCK(ap);
		error = uiomove((char *)ape->ape_record + ap->ap_qoffset,
		    toread, uio);
		if (error) {
			AUDIT_PIPE_SX_XUNLOCK(ap);
			return (error);
		}

		/*
		 * If the copy succeeded, update book-keeping, and if no
		 * bytes remain in the current record, free it.
		 */
		AUDIT_PIPE_LOCK(ap);
		KASSERT(TAILQ_FIRST(&ap->ap_queue) == ape,
		    ("audit_pipe_read: queue out of sync after uiomove"));
		ap->ap_qoffset += toread;
		KASSERT(ape->ape_record_len >= ap->ap_qoffset,
		    ("audit_pipe_read: record_len >= qoffset (2)"));
		if (ap->ap_qoffset == ape->ape_record_len) {
			TAILQ_REMOVE(&ap->ap_queue, ape, ape_queue);
			ap->ap_qbyteslen -= ape->ape_record_len;
			audit_pipe_entry_free(ape);
			ap->ap_qlen--;
			ap->ap_qoffset = 0;
		}
	}
	AUDIT_PIPE_UNLOCK(ap);
	AUDIT_PIPE_SX_XUNLOCK(ap);
	return (0);
}