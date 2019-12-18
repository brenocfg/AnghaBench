#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int fs_flags; char* fs_maxbpg; char* fs_avgfilesize; char* fs_avgfpdir; char* fs_minfree; char* fs_metaspace; scalar_t__ fs_optim; char* fs_volname; } ;

/* Variables and functions */
 int FS_ACLS ; 
 int FS_DOSOFTDEP ; 
 int FS_GJOURNAL ; 
 int FS_MULTILABEL ; 
 int FS_NFS4ACLS ; 
 scalar_t__ FS_OPTSPACE ; 
 scalar_t__ FS_OPTTIME ; 
 int FS_SUJ ; 
 int FS_TRIM ; 
 char* MINFREE ; 
 int /*<<< orphan*/  OPTWARN ; 
 TYPE_1__ sblock ; 
 int /*<<< orphan*/  warnx (char*,char*,...) ; 

__attribute__((used)) static void
printfs(void)
{
	warnx("POSIX.1e ACLs: (-a)                                %s",
		(sblock.fs_flags & FS_ACLS)? "enabled" : "disabled");
	warnx("NFSv4 ACLs: (-N)                                   %s",
		(sblock.fs_flags & FS_NFS4ACLS)? "enabled" : "disabled");
	warnx("MAC multilabel: (-l)                               %s",
		(sblock.fs_flags & FS_MULTILABEL)? "enabled" : "disabled");
	warnx("soft updates: (-n)                                 %s", 
		(sblock.fs_flags & FS_DOSOFTDEP)? "enabled" : "disabled");
	warnx("soft update journaling: (-j)                       %s", 
		(sblock.fs_flags & FS_SUJ)? "enabled" : "disabled");
	warnx("gjournal: (-J)                                     %s",
		(sblock.fs_flags & FS_GJOURNAL)? "enabled" : "disabled");
	warnx("trim: (-t)                                         %s", 
		(sblock.fs_flags & FS_TRIM)? "enabled" : "disabled");
	warnx("maximum blocks per file in a cylinder group: (-e)  %d",
	      sblock.fs_maxbpg);
	warnx("average file size: (-f)                            %d",
	      sblock.fs_avgfilesize);
	warnx("average number of files in a directory: (-s)       %d",
	      sblock.fs_avgfpdir);
	warnx("minimum percentage of free space: (-m)             %d%%",
	      sblock.fs_minfree);
	warnx("space to hold for metadata blocks: (-k)            %jd",
	      sblock.fs_metaspace);
	warnx("optimization preference: (-o)                      %s",
	      sblock.fs_optim == FS_OPTSPACE ? "space" : "time");
	if (sblock.fs_minfree >= MINFREE &&
	    sblock.fs_optim == FS_OPTSPACE)
		warnx(OPTWARN, "time", ">=", MINFREE);
	if (sblock.fs_minfree < MINFREE &&
	    sblock.fs_optim == FS_OPTTIME)
		warnx(OPTWARN, "space", "<", MINFREE);
	warnx("volume label: (-L)                                 %s",
		sblock.fs_volname);
}