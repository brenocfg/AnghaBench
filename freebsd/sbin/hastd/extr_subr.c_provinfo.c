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
struct stat {int st_size; int /*<<< orphan*/  st_mode; } ;
struct hast_resource {char* hr_localpath; int hr_localfd; int hr_local_mediasize; int hr_local_sectorsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGMEDIASIZE ; 
 int /*<<< orphan*/  DIOCGSECTORSIZE ; 
 int /*<<< orphan*/  EFTYPE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int fstat (int,struct stat*) ; 
 int ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pjdlog_errno (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  pjdlog_error (char*,char*) ; 

int
provinfo(struct hast_resource *res, bool dowrite)
{
	struct stat sb;

	PJDLOG_ASSERT(res->hr_localpath != NULL &&
	    res->hr_localpath[0] != '\0');

	if (res->hr_localfd == -1) {
		res->hr_localfd = open(res->hr_localpath,
		    dowrite ? O_RDWR : O_RDONLY);
		if (res->hr_localfd == -1) {
			pjdlog_errno(LOG_ERR, "Unable to open %s",
			    res->hr_localpath);
			return (-1);
		}
	}
	if (fstat(res->hr_localfd, &sb) == -1) {
		pjdlog_errno(LOG_ERR, "Unable to stat %s", res->hr_localpath);
		return (-1);
	}
	if (S_ISCHR(sb.st_mode)) {
		/*
		 * If this is character device, it is most likely GEOM provider.
		 */
		if (ioctl(res->hr_localfd, DIOCGMEDIASIZE,
		    &res->hr_local_mediasize) == -1) {
			pjdlog_errno(LOG_ERR,
			    "Unable obtain provider %s mediasize",
			    res->hr_localpath);
			return (-1);
		}
		if (ioctl(res->hr_localfd, DIOCGSECTORSIZE,
		    &res->hr_local_sectorsize) == -1) {
			pjdlog_errno(LOG_ERR,
			    "Unable obtain provider %s sectorsize",
			    res->hr_localpath);
			return (-1);
		}
	} else if (S_ISREG(sb.st_mode)) {
		/*
		 * We also support regular files for which we hardcode
		 * sector size of 512 bytes.
		 */
		res->hr_local_mediasize = sb.st_size;
		res->hr_local_sectorsize = 512;
	} else {
		/*
		 * We support no other file types.
		 */
		pjdlog_error("%s is neither GEOM provider nor regular file.",
		    res->hr_localpath);
		errno = EFTYPE;
		return (-1);
	}
	return (0);
}