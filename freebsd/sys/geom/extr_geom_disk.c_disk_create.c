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
struct disk {char* d_name; char* d_unit; int d_flags; int /*<<< orphan*/  d_ident; int /*<<< orphan*/  d_init_level; int /*<<< orphan*/ * d_geom; int /*<<< orphan*/  d_sectorsize; int /*<<< orphan*/ * d_devstat; int /*<<< orphan*/ * d_strategy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVSTAT_ALL_SUPPORTED ; 
 int /*<<< orphan*/  DEVSTAT_PRIORITY_MAX ; 
 int /*<<< orphan*/  DEVSTAT_TYPE_DIRECT ; 
 int DISKFLAG_RESERVED ; 
 int /*<<< orphan*/  DISK_INIT_NONE ; 
 int DISK_VERSION ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int SPECNAMELEN ; 
 int /*<<< orphan*/ * devstat_new_entry (scalar_t__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_disk_create ; 
 int /*<<< orphan*/  g_disk_ident_adjust (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_post_event (int /*<<< orphan*/ ,struct disk*,int /*<<< orphan*/ ,struct disk*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,...) ; 
 int strlen (scalar_t__*) ; 

void
disk_create(struct disk *dp, int version)
{

	if (version != DISK_VERSION) {
		printf("WARNING: Attempt to add disk %s%d %s",
		    dp->d_name, dp->d_unit,
		    " using incompatible ABI version of disk(9)\n");
		printf("WARNING: Ignoring disk %s%d\n",
		    dp->d_name, dp->d_unit);
		return;
	}
	if (dp->d_flags & DISKFLAG_RESERVED) {
		printf("WARNING: Attempt to add non-MPSAFE disk %s%d\n",
		    dp->d_name, dp->d_unit);
		printf("WARNING: Ignoring disk %s%d\n",
		    dp->d_name, dp->d_unit);
		return;
	}
	KASSERT(dp->d_strategy != NULL, ("disk_create need d_strategy"));
	KASSERT(dp->d_name != NULL, ("disk_create need d_name"));
	KASSERT(*dp->d_name != 0, ("disk_create need d_name"));
	KASSERT(strlen(dp->d_name) < SPECNAMELEN - 4, ("disk name too long"));
	if (dp->d_devstat == NULL)
		dp->d_devstat = devstat_new_entry(dp->d_name, dp->d_unit,
		    dp->d_sectorsize, DEVSTAT_ALL_SUPPORTED,
		    DEVSTAT_TYPE_DIRECT, DEVSTAT_PRIORITY_MAX);
	dp->d_geom = NULL;

	dp->d_init_level = DISK_INIT_NONE;

	g_disk_ident_adjust(dp->d_ident, sizeof(dp->d_ident));
	g_post_event(g_disk_create, dp, M_WAITOK, dp, NULL);
}