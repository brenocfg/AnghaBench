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
struct thread {int dummy; } ;
struct cdev {int dummy; } ;
struct __lock_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NFSLOCK ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct __lock_msg* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct __lock_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct __lock_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lm_link ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ nfslock_isopen ; 
 int /*<<< orphan*/  nfslock_list ; 
 int /*<<< orphan*/  nfslock_mtx ; 

__attribute__((used)) static int
nfslock_close(struct cdev *dev, int fflag, int devtype, struct thread *td)
{
	struct __lock_msg *lm;

	mtx_lock(&nfslock_mtx);
	nfslock_isopen = 0;
	while (!TAILQ_EMPTY(&nfslock_list)) {
		lm = TAILQ_FIRST(&nfslock_list);
		/* XXX: answer request */
		TAILQ_REMOVE(&nfslock_list, lm, lm_link);
		free(lm, M_NFSLOCK);
	}
	mtx_unlock(&nfslock_mtx);
	return (0);
}