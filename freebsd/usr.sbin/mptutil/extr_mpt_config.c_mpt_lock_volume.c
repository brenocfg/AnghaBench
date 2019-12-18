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
struct mpt_query_disk {int /*<<< orphan*/  devname; } ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  U8 ;

/* Variables and functions */
 int ENOENT ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  O_RDWR ; 
 char* _PATH_DEV ; 
 int errno ; 
 int mpt_query_disk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mpt_query_disk*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnc (int,char*) ; 

int
mpt_lock_volume(U8 VolumeBus, U8 VolumeID)
{
	char path[MAXPATHLEN];
	struct mpt_query_disk qd;
	int error, vfd;

	error = mpt_query_disk(VolumeBus, VolumeID, &qd);
	if (error == ENOENT)
		/*
		 * This means there isn't a CAM device associated with
		 * the volume, and thus it is already implicitly
		 * locked, so just return.
		 */
		return (0);
	if (error) {
		warnc(error, "Unable to lookup volume device name");
		return (error);
	}
	snprintf(path, sizeof(path), "%s%s", _PATH_DEV, qd.devname);
	vfd = open(path, O_RDWR);
	if (vfd < 0) {
		error = errno;
		warn("Unable to lock volume %s", qd.devname);
		return (error);
	}
	return (0);
}