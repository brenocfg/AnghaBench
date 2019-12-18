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
struct smbfs_args {scalar_t__ version; int flags; int /*<<< orphan*/  caseopt; int /*<<< orphan*/  dir_mode; int /*<<< orphan*/  file_mode; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  root_path; int /*<<< orphan*/  dev; } ;
struct mntarg {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int SMBFS_MOUNT_HAVE_NLS ; 
 int SMBFS_MOUNT_INTR ; 
 int SMBFS_MOUNT_NO_LONG ; 
 int SMBFS_MOUNT_SOFT ; 
 int SMBFS_MOUNT_STRONG ; 
 scalar_t__ SMBFS_VERSION ; 
 int copyin (void*,struct smbfs_args*,int) ; 
 int kernel_mount (struct mntarg*,int /*<<< orphan*/ ) ; 
 struct mntarg* mount_arg (struct mntarg*,char*,int /*<<< orphan*/ ,int) ; 
 struct mntarg* mount_argb (struct mntarg*,int,char*) ; 
 struct mntarg* mount_argf (struct mntarg*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
smbfs_cmount(struct mntarg *ma, void * data, uint64_t flags)
{
	struct smbfs_args args;
	int error;

	error = copyin(data, &args, sizeof(struct smbfs_args));
	if (error)
		return error;

	if (args.version != SMBFS_VERSION) {
		printf("mount version mismatch: kernel=%d, mount=%d\n",
		    SMBFS_VERSION, args.version);
		return EINVAL;
	}
	ma = mount_argf(ma, "dev", "%d", args.dev);
	ma = mount_argb(ma, args.flags & SMBFS_MOUNT_SOFT, "nosoft");
	ma = mount_argb(ma, args.flags & SMBFS_MOUNT_INTR, "nointr");
	ma = mount_argb(ma, args.flags & SMBFS_MOUNT_STRONG, "nostrong");
	ma = mount_argb(ma, args.flags & SMBFS_MOUNT_HAVE_NLS, "nohave_nls");
	ma = mount_argb(ma, !(args.flags & SMBFS_MOUNT_NO_LONG), "nolong");
	ma = mount_arg(ma, "rootpath", args.root_path, -1);
	ma = mount_argf(ma, "uid", "%d", args.uid);
	ma = mount_argf(ma, "gid", "%d", args.gid);
	ma = mount_argf(ma, "file_mode", "%d", args.file_mode);
	ma = mount_argf(ma, "dir_mode", "%d", args.dir_mode);
	ma = mount_argf(ma, "caseopt", "%d", args.caseopt);

	error = kernel_mount(ma, flags);

	return (error);
}