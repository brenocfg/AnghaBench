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
struct cdev {int dummy; } ;
struct __lock_msg {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  M_NFSLOCK ; 
 int PCATCH ; 
 int PSOCK ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct __lock_msg* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct __lock_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct __lock_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lm_link ; 
 int msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfslock_list ; 
 int /*<<< orphan*/  nfslock_mtx ; 
 int uiomove (struct __lock_msg*,int,struct uio*) ; 

__attribute__((used)) static int
nfslock_read(struct cdev *dev, struct uio *uio, int ioflag)
{
	int error;
	struct __lock_msg *lm;

	if (uio->uio_resid != sizeof *lm)
		return (EOPNOTSUPP);
	lm = NULL;
	error = 0;
	mtx_lock(&nfslock_mtx);
	while (TAILQ_EMPTY(&nfslock_list)) {
		error = msleep(&nfslock_list, &nfslock_mtx, PSOCK | PCATCH,
		    "nfslockd", 0);
		if (error)
			break;
	}
	if (!error) {
		lm = TAILQ_FIRST(&nfslock_list);
		TAILQ_REMOVE(&nfslock_list, lm, lm_link);
	}
	mtx_unlock(&nfslock_mtx);
	if (!error) {
		error = uiomove(lm, sizeof *lm, uio);
		free(lm, M_NFSLOCK);
	}
	return (error);
}