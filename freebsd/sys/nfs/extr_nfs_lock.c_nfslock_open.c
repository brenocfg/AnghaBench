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

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  PRIV_NFS_LOCKD ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int nfslock_isopen ; 
 int /*<<< orphan*/  nfslock_mtx ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfslock_open(struct cdev *dev, int oflags, int devtype, struct thread *td)
{
	int error;

	error = priv_check(td, PRIV_NFS_LOCKD);
	if (error)
		return (error);

	mtx_lock(&nfslock_mtx);
	if (!nfslock_isopen) {
		error = 0;
		nfslock_isopen = 1;
	} else {
		error = EOPNOTSUPP;
	}
	mtx_unlock(&nfslock_mtx);
		
	return (error);
}