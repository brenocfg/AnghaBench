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
struct lockd_ans {int dummy; } ;
struct cdev {int dummy; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  curthread ; 
 int nfslockdans (int /*<<< orphan*/ ,struct lockd_ans*) ; 
 int uiomove (struct lockd_ans*,int,struct uio*) ; 

__attribute__((used)) static int
nfslock_write(struct cdev *dev, struct uio *uio, int ioflag)
{
	struct lockd_ans la;
	int error;

	if (uio->uio_resid != sizeof la)
		return (EOPNOTSUPP);
	error = uiomove(&la, sizeof la, uio);
	if (!error)
		error = nfslockdans(curthread, &la);
	return (error);
}