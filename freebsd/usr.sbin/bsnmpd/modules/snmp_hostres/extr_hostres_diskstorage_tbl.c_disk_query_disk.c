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
struct disk_entry {char* dev_name; int capacity; int /*<<< orphan*/  index; } ;
typedef  int off_t ;
typedef  int /*<<< orphan*/  dev_path ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGMEDIASIZE ; 
 int /*<<< orphan*/  HRDBG (char*,char*,...) ; 
 int INT_MAX ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 char* _PATH_DEV ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  partition_tbl_handle_disk (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
disk_query_disk(struct disk_entry *entry)
{
	char dev_path[128];
	int fd;
	off_t mediasize;

	if (entry == NULL || entry->dev_name[0] == '\0')
		return;

	snprintf(dev_path, sizeof(dev_path),
	    "%s%s", _PATH_DEV, entry->dev_name);
	entry->capacity = 0;

	HRDBG("OPENING device %s", dev_path);
	if ((fd = open(dev_path, O_RDONLY|O_NONBLOCK)) == -1) {
		HRDBG("OPEN device %s failed: %s", dev_path, strerror(errno));
		return;
	}

	if (ioctl(fd, DIOCGMEDIASIZE, &mediasize) < 0) {
		HRDBG("DIOCGMEDIASIZE for device %s failed: %s",
		    dev_path, strerror(errno));
		(void)close(fd);
		return;
	}

	mediasize = mediasize / 1024;
	entry->capacity = (mediasize > INT_MAX ? INT_MAX : mediasize);
	partition_tbl_handle_disk(entry->index, entry->dev_name);

	(void)close(fd);
}