#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int PageLength; } ;
struct volume_info {int /*<<< orphan*/  VolumeID; int /*<<< orphan*/  VolumeBus; TYPE_1__ Header; } ;
struct config_id_state {int target_id; struct volume_info* ioc2; int /*<<< orphan*/ * list; struct volume_info* sdisks; int /*<<< orphan*/  nsdisks; } ;
struct TYPE_4__ {int raid_type; int /*<<< orphan*/ * name; } ;
typedef  struct volume_info CONFIG_PAGE_RAID_VOL_0 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MPI_RAID_ACTION_ADATA_DO_NOT_SYNC ; 
 int /*<<< orphan*/  MPI_RAID_ACTION_CREATE_VOLUME ; 
 int add_drives (int,struct volume_info*,int) ; 
 struct volume_info* build_volume (int,struct volume_info*,int,long,struct config_id_state*,int) ; 
 struct volume_info* calloc (int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 long dehumanize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dump_config (struct volume_info*) ; 
 int errno ; 
 int /*<<< orphan*/  free (struct volume_info*) ; 
 int getopt (int,char**,char*) ; 
 int mpt_fetch_disks (int,int /*<<< orphan*/ *,struct volume_info**) ; 
 int /*<<< orphan*/  mpt_free_pd_list (int /*<<< orphan*/ *) ; 
 int mpt_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mpt_pd_list (int) ; 
 int mpt_raid_action (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct volume_info*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct volume_info* mpt_read_ioc_page (int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpt_rescan_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mpt_unit ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 int parse_volume (int,int,struct config_id_state*,char*,struct volume_info*) ; 
 int /*<<< orphan*/  powerof2 (long) ; 
 TYPE_2__* raid_type_table ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static int
create_volume(int ac, char **av)
{
	CONFIG_PAGE_RAID_VOL_0 *vol;
	struct config_id_state state;
	struct volume_info *info;
	long stripe_size;
	int ch, error, fd, i, quick, raid_type, verbose;
#ifdef DEBUG
	int dump;
#endif

	if (ac < 2) {
		warnx("create: volume type required");
		return (EINVAL);
	}
	
	fd = mpt_open(mpt_unit);
	if (fd < 0) {
		error = errno;
		warn("mpt_open");
		return (error);
	}

	/* Lookup the RAID type first. */
	raid_type = -1;
	for (i = 0; raid_type_table[i].name != NULL; i++)
		if (strcasecmp(raid_type_table[i].name, av[1]) == 0) {
			raid_type = raid_type_table[i].raid_type;
			break;
		}

	if (raid_type == -1) {
		warnx("Unknown or unsupported volume type %s", av[1]);
		close(fd);
		return (EINVAL);
	}

	/* Parse any options. */
	optind = 2;
#ifdef DEBUG
	dump = 0;
#endif
	quick = 0;
	verbose = 0;
	stripe_size = 64 * 1024;

	while ((ch = getopt(ac, av, "dqs:v")) != -1) {
		switch (ch) {
#ifdef DEBUG
		case 'd':
			dump = 1;
			break;
#endif
		case 'q':
			quick = 1;
			break;
		case 's':
			stripe_size = dehumanize(optarg);
			if ((stripe_size < 512) || (!powerof2(stripe_size))) {
				warnx("Invalid stripe size %s", optarg);
				close(fd);
				return (EINVAL);
			}
			break;
		case 'v':
			verbose = 1;
			break;
		case '?':
		default:
			close(fd);
			return (EINVAL);
		}
	}
	ac -= optind;
	av += optind;

	/* Fetch existing config data. */
	state.ioc2 = mpt_read_ioc_page(fd, 2, NULL);
	if (state.ioc2 == NULL) {
		error = errno;
		warn("Failed to read volume list");
		close(fd);
		return (error);
	}
	state.list = mpt_pd_list(fd);
	if (state.list == NULL) {
		close(fd);
		return (errno);
	}
	error = mpt_fetch_disks(fd, &state.nsdisks, &state.sdisks);
	if (error) {
		warn("Failed to fetch standalone disk list");
		close(fd);
		return (error);
	}	
	state.target_id = 0xff;
	
	/* Parse the drive list. */
	if (ac != 1) {
		warnx("Exactly one drive list is required");
		close(fd);
		return (EINVAL);
	}
	info = calloc(1, sizeof(*info));
	if (info == NULL) {
		close(fd);
		return (ENOMEM);
	}
	error = parse_volume(fd, raid_type, &state, av[0], info);
	if (error) {
		free(info);
		close(fd);
		return (error);
	}

	/* Create RAID physdisk pages for standalone disks. */
	error = add_drives(fd, info, verbose);
	if (error) {
		free(info);
		close(fd);
		return (error);
	}

	/* Build the volume. */
	vol = build_volume(fd, info, raid_type, stripe_size, &state, verbose);
	if (vol == NULL) {
		free(info);
		close(fd);
		return (errno);
	}

#ifdef DEBUG
	if (dump) {
		dump_config(vol);
		goto skip;
	}
#endif

	/* Send the new volume to the controller. */
	error = mpt_raid_action(fd, MPI_RAID_ACTION_CREATE_VOLUME, vol->VolumeBus,
	    vol->VolumeID, 0, quick ? MPI_RAID_ACTION_ADATA_DO_NOT_SYNC : 0,
	    vol, vol->Header.PageLength * 4, NULL, NULL, 0, NULL, NULL, 1);
	if (error) {
		errno = error;
		warn("Failed to add volume");
		free(info);
		close(fd);
		return (error);
	}

#ifdef DEBUG
skip:
#endif
	mpt_rescan_bus(vol->VolumeBus, vol->VolumeID);

	/* Clean up. */
	free(vol);
	free(info);
	free(state.sdisks);
	mpt_free_pd_list(state.list);
	free(state.ioc2);
	close(fd);

	return (0);
}