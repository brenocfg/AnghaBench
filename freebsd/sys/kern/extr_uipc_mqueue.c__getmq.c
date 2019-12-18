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
struct mqueue {int dummy; } ;
struct mqfs_node {struct mqueue* mn_data; } ;
struct file {struct mqfs_node* f_data; int /*<<< orphan*/ * f_ops; } ;
typedef  int /*<<< orphan*/  cap_rights_t ;
typedef  int (* _fgetf ) (struct thread*,int,int /*<<< orphan*/ *,struct file**) ;

/* Variables and functions */
 int EBADF ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int /*<<< orphan*/  mqueueops ; 

__attribute__((used)) static int
_getmq(struct thread *td, int fd, cap_rights_t *rightsp, _fgetf func,
       struct file **fpp, struct mqfs_node **ppn, struct mqueue **pmq)
{
	struct mqfs_node *pn;
	int error;

	error = func(td, fd, rightsp, fpp);
	if (error)
		return (error);
	if (&mqueueops != (*fpp)->f_ops) {
		fdrop(*fpp, td);
		return (EBADF);
	}
	pn = (*fpp)->f_data;
	if (ppn)
		*ppn = pn;
	if (pmq)
		*pmq = pn->mn_data;
	return (0);
}