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
typedef  char const* uintmax_t ;
struct vnstat {scalar_t__ vn_type; char const* vn_mntdir; int vn_mode; char const* vn_devname; scalar_t__ vn_size; scalar_t__ vn_dev; scalar_t__ vn_fileid; scalar_t__ vn_fsid; } ;
struct procstat {int dummy; } ;
struct filestat {int /*<<< orphan*/  fs_fflags; } ;
typedef  int /*<<< orphan*/  mode ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 scalar_t__ PS_FST_VTYPE_VBAD ; 
 scalar_t__ PS_FST_VTYPE_VBLK ; 
 scalar_t__ PS_FST_VTYPE_VCHR ; 
 scalar_t__ PS_FST_VTYPE_VNON ; 
 int _POSIX2_LINE_MAX ; 
 scalar_t__ nflg ; 
 int /*<<< orphan*/  print_access_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 int procstat_get_vnode_info (struct procstat*,struct filestat*,struct vnstat*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  strmode (int,char*) ; 

__attribute__((used)) static void
print_vnode_info(struct procstat *procstat, struct filestat *fst)
{
	struct vnstat vn;
	char errbuf[_POSIX2_LINE_MAX];
	char mode[15];
	const char *badtype;
	int error;

	badtype = NULL;
	error = procstat_get_vnode_info(procstat, fst, &vn, errbuf);
	if (error != 0)
		badtype = errbuf;
	else if (vn.vn_type == PS_FST_VTYPE_VBAD)
		badtype = "bad";
	else if (vn.vn_type == PS_FST_VTYPE_VNON)
		badtype = "none";
	if (badtype != NULL) {
		printf(" -         -  %10s    -", badtype);
		return;
	}

	if (nflg)
		printf(" %#5jx", (uintmax_t)vn.vn_fsid);
	else if (vn.vn_mntdir != NULL)
		(void)printf(" %-8s", vn.vn_mntdir);

	/*
	 * Print access mode.
	 */
	if (nflg)
		(void)snprintf(mode, sizeof(mode), "%o", vn.vn_mode);
	else {
		strmode(vn.vn_mode, mode);
	}
	(void)printf(" %6jd %10s", (intmax_t)vn.vn_fileid, mode);

	if (vn.vn_type == PS_FST_VTYPE_VBLK || vn.vn_type == PS_FST_VTYPE_VCHR) {
		if (nflg || !*vn.vn_devname)
			printf(" %#6jx", (uintmax_t)vn.vn_dev);
		else {
			printf(" %6s", vn.vn_devname);
		}
	} else
		printf(" %6ju", (uintmax_t)vn.vn_size);
	print_access_flags(fst->fs_fflags);
}