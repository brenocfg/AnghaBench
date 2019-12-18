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
typedef  int /*<<< orphan*/  uint64_t ;
struct ufs_args {int /*<<< orphan*/  fspec; int /*<<< orphan*/  export; } ;
struct mntarg {int dummy; } ;
struct export_args {int dummy; } ;
typedef  int /*<<< orphan*/  exp ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 int copyin (void*,struct ufs_args*,int) ; 
 int kernel_mount (struct mntarg*,int /*<<< orphan*/ ) ; 
 struct mntarg* mount_arg (struct mntarg*,char*,struct export_args*,int) ; 
 struct mntarg* mount_argsu (struct mntarg*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_oexport_conv (int /*<<< orphan*/ *,struct export_args*) ; 

__attribute__((used)) static int
ffs_cmount(struct mntarg *ma, void *data, uint64_t flags)
{
	struct ufs_args args;
	struct export_args exp;
	int error;

	if (data == NULL)
		return (EINVAL);
	error = copyin(data, &args, sizeof args);
	if (error)
		return (error);
	vfs_oexport_conv(&args.export, &exp);

	ma = mount_argsu(ma, "from", args.fspec, MAXPATHLEN);
	ma = mount_arg(ma, "export", &exp, sizeof(exp));
	error = kernel_mount(ma, flags);

	return (error);
}