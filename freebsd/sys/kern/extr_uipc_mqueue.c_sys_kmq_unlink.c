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
struct mqfs_node {int dummy; } ;
struct kmq_unlink_args {int /*<<< orphan*/  path; } ;
struct TYPE_2__ {int /*<<< orphan*/  mi_lock; int /*<<< orphan*/  mi_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_UPATH1_CANON (char*) ; 
 int EINVAL ; 
 int ENOENT ; 
 int MQFS_NAMELEN ; 
 int copyinstr (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *) ; 
 int do_unlink (struct mqfs_node*,int /*<<< orphan*/ ) ; 
 TYPE_1__ mqfs_data ; 
 struct mqfs_node* mqfs_search (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

int
sys_kmq_unlink(struct thread *td, struct kmq_unlink_args *uap)
{
	char path[MQFS_NAMELEN+1];
	struct mqfs_node *pn;
	int error, len;

	error = copyinstr(uap->path, path, MQFS_NAMELEN + 1, NULL);
        if (error)
		return (error);

	len = strlen(path);
	if (len < 2 || path[0] != '/' || strchr(path + 1, '/') != NULL)
		return (EINVAL);
	if (strcmp(path, "/.") == 0 || strcmp(path, "/..") == 0)
		return (EINVAL);
	AUDIT_ARG_UPATH1_CANON(path);

	sx_xlock(&mqfs_data.mi_lock);
	pn = mqfs_search(mqfs_data.mi_root, path + 1, len - 1, td->td_ucred);
	if (pn != NULL)
		error = do_unlink(pn, td->td_ucred);
	else
		error = ENOENT;
	sx_xunlock(&mqfs_data.mi_lock);
	return (error);
}