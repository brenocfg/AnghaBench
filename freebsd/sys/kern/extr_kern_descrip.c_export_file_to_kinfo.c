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
struct kinfo_file {int kf_fd; int /*<<< orphan*/  kf_structsize; int /*<<< orphan*/  kf_status; int /*<<< orphan*/  kf_offset; int /*<<< orphan*/  kf_ref_count; int /*<<< orphan*/  kf_cap_rights; int /*<<< orphan*/  kf_flags; int /*<<< orphan*/  kf_type; } ;
struct filedesc {int dummy; } ;
struct file {int /*<<< orphan*/  f_count; int /*<<< orphan*/  f_flag; } ;
typedef  int /*<<< orphan*/  cap_rights_t ;

/* Variables and functions */
 int KERN_FILEDESC_PACK_KINFO ; 
 int /*<<< orphan*/  KF_ATTR_VALID ; 
 int /*<<< orphan*/  KF_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  bzero (struct kinfo_file*,int) ; 
 int /*<<< orphan*/  cap_rights_init (int /*<<< orphan*/ *) ; 
 int fo_fill_kinfo (struct file*,struct kinfo_file*,struct filedesc*) ; 
 int /*<<< orphan*/  foffset_get (struct file*) ; 
 int /*<<< orphan*/  pack_kinfo (struct kinfo_file*) ; 
 int /*<<< orphan*/  roundup2 (int,int) ; 
 int /*<<< orphan*/  xlate_fflags (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
export_file_to_kinfo(struct file *fp, int fd, cap_rights_t *rightsp,
    struct kinfo_file *kif, struct filedesc *fdp, int flags)
{
	int error;

	bzero(kif, sizeof(*kif));

	/* Set a default type to allow for empty fill_kinfo() methods. */
	kif->kf_type = KF_TYPE_UNKNOWN;
	kif->kf_flags = xlate_fflags(fp->f_flag);
	if (rightsp != NULL)
		kif->kf_cap_rights = *rightsp;
	else
		cap_rights_init(&kif->kf_cap_rights);
	kif->kf_fd = fd;
	kif->kf_ref_count = fp->f_count;
	kif->kf_offset = foffset_get(fp);

	/*
	 * This may drop the filedesc lock, so the 'fp' cannot be
	 * accessed after this call.
	 */
	error = fo_fill_kinfo(fp, kif, fdp);
	if (error == 0)
		kif->kf_status |= KF_ATTR_VALID;
	if ((flags & KERN_FILEDESC_PACK_KINFO) != 0)
		pack_kinfo(kif);
	else
		kif->kf_structsize = roundup2(sizeof(*kif), sizeof(uint64_t));
}