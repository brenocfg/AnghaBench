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
struct timespec {int dummy; } ;
struct vattr {int va_type; int va_mode; int va_nlink; int va_filerev; struct timespec va_birthtime; struct timespec va_ctime; struct timespec va_mtime; struct timespec va_atime; scalar_t__ va_vaflags; scalar_t__ va_bytes; int /*<<< orphan*/  va_rdev; scalar_t__ va_flags; int /*<<< orphan*/  va_gen; int /*<<< orphan*/  va_blocksize; scalar_t__ va_size; int /*<<< orphan*/  va_fileid; scalar_t__ va_gid; scalar_t__ va_uid; } ;
struct timeval {int dummy; } ;
typedef  int /*<<< orphan*/  ino_t ;
typedef  enum vtype { ____Placeholder_vtype } vtype ;

/* Variables and functions */
 int /*<<< orphan*/  PUFFS_VNOVAL ; 
 int /*<<< orphan*/  TIMEVAL_TO_TIMESPEC (struct timeval*,struct timespec*) ; 
 int VDIR ; 
 int /*<<< orphan*/  getpagesize () ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  random () ; 

void
dtfs_baseattrs(struct vattr *vap, enum vtype type, ino_t id)
{
	struct timeval tv;
	struct timespec ts;

	gettimeofday(&tv, NULL);
	TIMEVAL_TO_TIMESPEC(&tv, &ts);

	vap->va_type = type;
	if (type == VDIR) {
		vap->va_mode = 0777;
		vap->va_nlink = 1;	/* n + 1 after adding dent */
	} else {
		vap->va_mode = 0666;
		vap->va_nlink = 0;	/* n + 1 */
	}
	vap->va_uid = 0;
	vap->va_gid = 0;
	vap->va_fileid = id;
	vap->va_size = 0;
	vap->va_blocksize = getpagesize();
	vap->va_gen = random();
	vap->va_flags = 0;
	vap->va_rdev = PUFFS_VNOVAL;
	vap->va_bytes = 0;
	vap->va_filerev = 1;
	vap->va_vaflags = 0;

	vap->va_atime = vap->va_mtime = vap->va_ctime = vap->va_birthtime = ts;
}