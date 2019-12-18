#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint64_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct vnstat {int fs_uflags; int vn_type; void* vn_dev; int /*<<< orphan*/  vn_mode; void* vn_size; void* vn_fileid; void* vn_fsid; int /*<<< orphan*/  vn_devname; void* vn_mntdir; struct kinfo_vmentry* fs_typedep; } ;
struct statfs {char* f_mntonname; } ;
struct TYPE_3__ {void* kf_file_size; void* kf_file_rdev; int /*<<< orphan*/  kf_file_mode; void* kf_file_fsid; void* kf_file_fileid; } ;
struct TYPE_4__ {TYPE_1__ kf_file; } ;
struct kinfo_vmentry {char* kve_path; int kve_status; char* kf_path; int kf_status; int /*<<< orphan*/  kf_vnode_type; TYPE_2__ kf_un; int /*<<< orphan*/  kve_vn_type; void* kve_vn_size; void* kve_vn_rdev; int /*<<< orphan*/  kve_vn_mode; void* kve_vn_fsid; void* kve_vn_fileid; } ;
struct kinfo_file {char* kve_path; int kve_status; char* kf_path; int kf_status; int /*<<< orphan*/  kf_vnode_type; TYPE_2__ kf_un; int /*<<< orphan*/  kve_vn_type; void* kve_vn_size; void* kve_vn_rdev; int /*<<< orphan*/  kve_vn_mode; void* kve_vn_fsid; void* kve_vn_fileid; } ;
struct filestat {int fs_uflags; int vn_type; void* vn_dev; int /*<<< orphan*/  vn_mode; void* vn_size; void* vn_fileid; void* vn_fsid; int /*<<< orphan*/  vn_devname; void* vn_mntdir; struct kinfo_vmentry* fs_typedep; } ;

/* Variables and functions */
 int KF_ATTR_VALID ; 
 int PS_FST_UFLAG_MMAP ; 
 int PS_FST_VTYPE_VBAD ; 
 int PS_FST_VTYPE_VBLK ; 
 int PS_FST_VTYPE_VCHR ; 
 int PS_FST_VTYPE_VNON ; 
 int /*<<< orphan*/  S_IFBLK ; 
 int /*<<< orphan*/  S_IFCHR ; 
 int /*<<< orphan*/  _POSIX2_LINE_MAX ; 
 int /*<<< orphan*/  assert (struct vnstat*) ; 
 int /*<<< orphan*/  bzero (struct vnstat*,int) ; 
 char* devname (void*,int /*<<< orphan*/ ) ; 
 int kinfo_vtype2fst (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  statfs (char*,struct statfs*) ; 
 void* strdup (char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
procstat_get_vnode_info_sysctl(struct filestat *fst, struct vnstat *vn,
    char *errbuf)
{
	struct statfs stbuf;
	struct kinfo_file *kif;
	struct kinfo_vmentry *kve;
	char *name, *path;
	uint64_t fileid;
	uint64_t size;
	uint64_t fsid;
	uint64_t rdev;
	uint16_t mode;
	int vntype;
	int status;

	assert(fst);
	assert(vn);
	bzero(vn, sizeof(*vn));
	if (fst->fs_typedep == NULL)
		return (1);
	if (fst->fs_uflags & PS_FST_UFLAG_MMAP) {
		kve = fst->fs_typedep;
		fileid = kve->kve_vn_fileid;
		fsid = kve->kve_vn_fsid;
		mode = kve->kve_vn_mode;
		path = kve->kve_path;
		rdev = kve->kve_vn_rdev;
		size = kve->kve_vn_size;
		vntype = kinfo_vtype2fst(kve->kve_vn_type);
		status = kve->kve_status;
	} else {
		kif = fst->fs_typedep;
		fileid = kif->kf_un.kf_file.kf_file_fileid;
		fsid = kif->kf_un.kf_file.kf_file_fsid;
		mode = kif->kf_un.kf_file.kf_file_mode;
		path = kif->kf_path;
		rdev = kif->kf_un.kf_file.kf_file_rdev;
		size = kif->kf_un.kf_file.kf_file_size;
		vntype = kinfo_vtype2fst(kif->kf_vnode_type);
		status = kif->kf_status;
	}
	vn->vn_type = vntype;
	if (vntype == PS_FST_VTYPE_VNON || vntype == PS_FST_VTYPE_VBAD)
		return (0);
	if ((status & KF_ATTR_VALID) == 0) {
		if (errbuf != NULL) {
			snprintf(errbuf, _POSIX2_LINE_MAX,
			    "? (no info available)");
		}
		return (1);
	}
	if (path && *path) {
		statfs(path, &stbuf);
		vn->vn_mntdir = strdup(stbuf.f_mntonname);
	} else
		vn->vn_mntdir = strdup("-");
	vn->vn_dev = rdev;
	if (vntype == PS_FST_VTYPE_VBLK) {
		name = devname(rdev, S_IFBLK);
		if (name != NULL)
			strlcpy(vn->vn_devname, name,
			    sizeof(vn->vn_devname));
	} else if (vntype == PS_FST_VTYPE_VCHR) {
		name = devname(vn->vn_dev, S_IFCHR);
		if (name != NULL)
			strlcpy(vn->vn_devname, name,
			    sizeof(vn->vn_devname));
	}
	vn->vn_fsid = fsid;
	vn->vn_fileid = fileid;
	vn->vn_size = size;
	vn->vn_mode = mode;
	return (0);
}