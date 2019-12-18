#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_int ;
typedef  void* off_t ;
struct TYPE_3__ {int /*<<< orphan*/ * ud_bcache; scalar_t__ ud_open; void* sectorsize; void* mediasize; } ;

/* Variables and functions */
 scalar_t__ CALLBACK (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  DIOCGMEDIASIZE ; 
 int /*<<< orphan*/  DIOCGSECTORSIZE ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  bcache_add_dev (int) ; 
 int /*<<< orphan*/  diskioctl ; 
 TYPE_1__* malloc (int) ; 
 TYPE_1__* ud_info ; 
 int userboot_disk_maxunit ; 
 int userdisk_maxunit ; 

__attribute__((used)) static int
userdisk_init(void)
{
	off_t mediasize;
	u_int sectorsize;
	int i;

	userdisk_maxunit = userboot_disk_maxunit;
	if (userdisk_maxunit > 0) {
		ud_info = malloc(sizeof(*ud_info) * userdisk_maxunit);
		if (ud_info == NULL)
			return (ENOMEM);
		for (i = 0; i < userdisk_maxunit; i++) {
			if (CALLBACK(diskioctl, i, DIOCGSECTORSIZE,
			    &sectorsize) != 0 || CALLBACK(diskioctl, i,
			    DIOCGMEDIASIZE, &mediasize) != 0)
				return (ENXIO);
			ud_info[i].mediasize = mediasize;
			ud_info[i].sectorsize = sectorsize;
			ud_info[i].ud_open = 0;
			ud_info[i].ud_bcache = NULL;
		}
	}
	bcache_add_dev(userdisk_maxunit);
	return(0);
}