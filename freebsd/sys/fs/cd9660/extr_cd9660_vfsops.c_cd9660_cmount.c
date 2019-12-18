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
struct mntarg {int dummy; } ;
struct iso_args {int flags; int /*<<< orphan*/  ssector; int /*<<< orphan*/  cs_local; int /*<<< orphan*/  cs_disk; int /*<<< orphan*/  fspec; int /*<<< orphan*/  export; } ;
struct export_args {int dummy; } ;
typedef  int /*<<< orphan*/  exp ;

/* Variables and functions */
 int ISOFSMNT_BROKENJOLIET ; 
 int ISOFSMNT_EXTATT ; 
 int ISOFSMNT_GENS ; 
 int ISOFSMNT_KICONV ; 
 int ISOFSMNT_NOJOLIET ; 
 int ISOFSMNT_NORRIP ; 
 int MAXPATHLEN ; 
 int copyin (void*,struct iso_args*,int) ; 
 int kernel_mount (struct mntarg*,int /*<<< orphan*/ ) ; 
 struct mntarg* mount_arg (struct mntarg*,char*,struct export_args*,int) ; 
 struct mntarg* mount_argb (struct mntarg*,int,char*) ; 
 struct mntarg* mount_argf (struct mntarg*,char*,char*,int /*<<< orphan*/ ) ; 
 struct mntarg* mount_argsu (struct mntarg*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfs_oexport_conv (int /*<<< orphan*/ *,struct export_args*) ; 

__attribute__((used)) static int
cd9660_cmount(struct mntarg *ma, void *data, uint64_t flags)
{
	struct iso_args args;
	struct export_args exp;
	int error;

	error = copyin(data, &args, sizeof args);
	if (error)
		return (error);
	vfs_oexport_conv(&args.export, &exp);

	ma = mount_argsu(ma, "from", args.fspec, MAXPATHLEN);
	ma = mount_arg(ma, "export", &exp, sizeof(exp));
	ma = mount_argsu(ma, "cs_disk", args.cs_disk, 64);
	ma = mount_argsu(ma, "cs_local", args.cs_local, 64);
	ma = mount_argf(ma, "ssector", "%u", args.ssector);
	ma = mount_argb(ma, !(args.flags & ISOFSMNT_NORRIP), "norrip");
	ma = mount_argb(ma, args.flags & ISOFSMNT_GENS, "nogens");
	ma = mount_argb(ma, args.flags & ISOFSMNT_EXTATT, "noextatt");
	ma = mount_argb(ma, !(args.flags & ISOFSMNT_NOJOLIET), "nojoliet");
	ma = mount_argb(ma,
	    args.flags & ISOFSMNT_BROKENJOLIET, "nobrokenjoliet");
	ma = mount_argb(ma, args.flags & ISOFSMNT_KICONV, "nokiconv");

	error = kernel_mount(ma, flags);

	return (error);
}