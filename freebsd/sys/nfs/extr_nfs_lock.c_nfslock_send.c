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
struct __lock_msg {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  M_NFSLOCK ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct __lock_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct __lock_msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lm_link ; 
 struct __lock_msg* malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct __lock_msg*,struct __lock_msg*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ nfslock_isopen ; 
 int /*<<< orphan*/  nfslock_list ; 
 int /*<<< orphan*/  nfslock_mtx ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
nfslock_send(struct __lock_msg *lm)
{
	struct __lock_msg *lm2;
	int error;

	error = 0;
	lm2 = malloc(sizeof *lm2, M_NFSLOCK, M_WAITOK);
	mtx_lock(&nfslock_mtx);
	if (nfslock_isopen) {
		memcpy(lm2, lm, sizeof *lm2);
		TAILQ_INSERT_TAIL(&nfslock_list, lm2, lm_link);
		wakeup(&nfslock_list);
	} else {
		error = EOPNOTSUPP;
	}
	mtx_unlock(&nfslock_mtx);
	if (error)
		free(lm2, M_NFSLOCK);
	return (error);
}