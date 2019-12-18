#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct mpt_standalone_disk {int /*<<< orphan*/  target; int /*<<< orphan*/  bus; } ;
typedef  int U8 ;
typedef  int U32 ;
struct TYPE_9__ {scalar_t__ PageVersion; } ;
struct TYPE_7__ {int PageLength; scalar_t__ PageNumber; int /*<<< orphan*/  PageType; } ;
struct TYPE_8__ {int /*<<< orphan*/  PhysDiskID; int /*<<< orphan*/  PhysDiskBus; scalar_t__ PhysDiskIOC; TYPE_1__ Header; } ;
typedef  TYPE_2__ CONFIG_PAGE_RAID_PHYS_DISK_0 ;
typedef  TYPE_3__ CONFIG_PAGE_HEADER ;
typedef  int /*<<< orphan*/  ActionData ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MPI_CONFIG_PAGETYPE_RAID_PHYSDISK ; 
 scalar_t__ MPI_RAIDPHYSDISKPAGE0_PAGEVERSION ; 
 int /*<<< orphan*/  MPI_RAID_ACTION_CREATE_PHYSDISK ; 
 TYPE_2__* calloc (int,int) ; 
 int mpt_raid_action (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int,int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int mpt_read_config_page_header (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warnx (char*,scalar_t__) ; 

__attribute__((used)) static int
mpt_create_physdisk(int fd, struct mpt_standalone_disk *disk, U8 *PhysDiskNum)
{
	CONFIG_PAGE_HEADER header;
	CONFIG_PAGE_RAID_PHYS_DISK_0 *config_page;
	int error;
	U32 ActionData;

	error = mpt_read_config_page_header(fd, MPI_CONFIG_PAGETYPE_RAID_PHYSDISK,
	    0, 0, &header, NULL);
	if (error)
		return (error);
	if (header.PageVersion > MPI_RAIDPHYSDISKPAGE0_PAGEVERSION) {
		warnx("Unsupported RAID physdisk page 0 version %d",
		    header.PageVersion);
		return (EOPNOTSUPP);
	}		
	config_page = calloc(1, sizeof(CONFIG_PAGE_RAID_PHYS_DISK_0));
	config_page->Header.PageType = MPI_CONFIG_PAGETYPE_RAID_PHYSDISK;
	config_page->Header.PageNumber = 0;
	config_page->Header.PageLength = sizeof(CONFIG_PAGE_RAID_PHYS_DISK_0) /
	    4;
	config_page->PhysDiskIOC = 0;	/* XXX */
	config_page->PhysDiskBus = disk->bus;
	config_page->PhysDiskID = disk->target;

	/* XXX: Enclosure info for PhysDiskSettings? */
	error = mpt_raid_action(fd, MPI_RAID_ACTION_CREATE_PHYSDISK, 0, 0, 0, 0,
	    config_page, sizeof(CONFIG_PAGE_RAID_PHYS_DISK_0), NULL,
	    &ActionData, sizeof(ActionData), NULL, NULL, 1);
	if (error)
		return (error);
	*PhysDiskNum = ActionData & 0xff;
	return (0);
}