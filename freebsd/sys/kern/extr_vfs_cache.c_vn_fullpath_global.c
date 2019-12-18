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
struct vnode {int dummy; } ;
struct thread {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 scalar_t__ __predict_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disablefullpath ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rootvnode ; 
 int vn_fullpath1 (struct thread*,struct vnode*,int /*<<< orphan*/ ,char*,char**,int /*<<< orphan*/ ) ; 

int
vn_fullpath_global(struct thread *td, struct vnode *vn,
    char **retbuf, char **freebuf)
{
	char *buf;
	int error;

	if (__predict_false(disablefullpath))
		return (ENODEV);
	if (__predict_false(vn == NULL))
		return (EINVAL);
	buf = malloc(MAXPATHLEN, M_TEMP, M_WAITOK);
	error = vn_fullpath1(td, vn, rootvnode, buf, retbuf, MAXPATHLEN);
	if (!error)
		*freebuf = buf;
	else
		free(buf, M_TEMP);
	return (error);
}