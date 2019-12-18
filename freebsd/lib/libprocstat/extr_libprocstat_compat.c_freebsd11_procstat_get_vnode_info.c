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
struct vnstat {int /*<<< orphan*/  vn_devname; int /*<<< orphan*/  vn_mode; int /*<<< orphan*/  vn_type; int /*<<< orphan*/  vn_fsid; int /*<<< orphan*/  vn_dev; int /*<<< orphan*/  vn_mntdir; int /*<<< orphan*/  vn_size; int /*<<< orphan*/  vn_fileid; } ;
struct procstat {int dummy; } ;
struct freebsd11_vnstat {int /*<<< orphan*/  vn_devname; int /*<<< orphan*/  vn_mode; int /*<<< orphan*/  vn_type; int /*<<< orphan*/  vn_fsid; int /*<<< orphan*/  vn_dev; int /*<<< orphan*/  vn_mntdir; int /*<<< orphan*/  vn_size; int /*<<< orphan*/  vn_fileid; } ;
struct filestat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int procstat_get_vnode_info (struct procstat*,struct filestat*,struct vnstat*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trunc_name ; 

int
freebsd11_procstat_get_vnode_info(struct procstat *procstat,
    struct filestat *fst, struct freebsd11_vnstat *vn_compat, char *errbuf)
{
	struct vnstat vn;
	int r;

	r = procstat_get_vnode_info(procstat, fst, &vn, errbuf);
	if (r != 0)
		return (r);
	vn_compat->vn_fileid = vn.vn_fileid;
	vn_compat->vn_size = vn.vn_size;
	vn_compat->vn_mntdir = vn.vn_mntdir;
	vn_compat->vn_dev = vn.vn_dev;
	vn_compat->vn_fsid = vn.vn_fsid;
	vn_compat->vn_type = vn.vn_type;
	vn_compat->vn_mode = vn.vn_mode;
	if (strlen(vn.vn_devname) >= sizeof(vn_compat->vn_devname))
		strcpy(vn_compat->vn_devname, trunc_name);
	else
		memcpy(vn_compat->vn_devname, vn.vn_devname,
		    sizeof(vn_compat->vn_devname));
	return (0);
}