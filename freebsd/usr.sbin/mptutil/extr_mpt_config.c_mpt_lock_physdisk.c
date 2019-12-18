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
struct mpt_standalone_disk {int /*<<< orphan*/  devname; } ;
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int /*<<< orphan*/  O_RDWR ; 
 char* _PATH_DEV ; 
 int errno ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mpt_lock_physdisk(struct mpt_standalone_disk *disk)
{
	char path[MAXPATHLEN];
	int dfd, error;

	snprintf(path, sizeof(path), "%s%s", _PATH_DEV, disk->devname);
	dfd = open(path, O_RDWR);
	if (dfd < 0) {
		error = errno;
		warn("Unable to lock disk %s", disk->devname);
		return (error);
	}
	return (0);
}