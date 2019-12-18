#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct TYPE_2__ {struct thread* cn_thread; } ;
struct nameidata {TYPE_1__ ni_cnd; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int vn_open_cred (struct nameidata*,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct file*) ; 

int
vn_open(struct nameidata *ndp, int *flagp, int cmode, struct file *fp)
{
	struct thread *td = ndp->ni_cnd.cn_thread;

	return (vn_open_cred(ndp, flagp, cmode, 0, td->td_ucred, fp));
}