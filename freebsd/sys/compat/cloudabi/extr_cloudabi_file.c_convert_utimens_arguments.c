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
struct timespec {int tv_nsec; int tv_sec; } ;
typedef  int cloudabi_fsflags_t ;
struct TYPE_3__ {int st_atim; int st_mtim; } ;
typedef  TYPE_1__ cloudabi_filestat_t ;

/* Variables and functions */
 int CLOUDABI_FILESTAT_ATIM ; 
 int CLOUDABI_FILESTAT_ATIM_NOW ; 
 int CLOUDABI_FILESTAT_MTIM ; 
 int CLOUDABI_FILESTAT_MTIM_NOW ; 
 void* UTIME_NOW ; 
 void* UTIME_OMIT ; 

__attribute__((used)) static void
convert_utimens_arguments(const cloudabi_filestat_t *fs,
    cloudabi_fsflags_t flags, struct timespec *ts)
{

	if ((flags & CLOUDABI_FILESTAT_ATIM_NOW) != 0) {
		ts[0].tv_nsec = UTIME_NOW;
	} else if ((flags & CLOUDABI_FILESTAT_ATIM) != 0) {
		ts[0].tv_sec = fs->st_atim / 1000000000;
		ts[0].tv_nsec = fs->st_atim % 1000000000;
	} else {
		ts[0].tv_nsec = UTIME_OMIT;
	}

	if ((flags & CLOUDABI_FILESTAT_MTIM_NOW) != 0) {
		ts[1].tv_nsec = UTIME_NOW;
	} else if ((flags & CLOUDABI_FILESTAT_MTIM) != 0) {
		ts[1].tv_sec = fs->st_mtim / 1000000000;
		ts[1].tv_nsec = fs->st_mtim % 1000000000;
	} else {
		ts[1].tv_nsec = UTIME_OMIT;
	}
}