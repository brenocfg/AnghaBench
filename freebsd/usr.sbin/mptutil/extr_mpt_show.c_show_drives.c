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
struct mpt_standalone_disk {char* devname; } ;
struct mpt_drive_list {int ndrives; TYPE_1__** drives; } ;
struct TYPE_3__ {int PhysDiskNum; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  STANDALONE_STATE ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  free (struct mpt_standalone_disk*) ; 
 scalar_t__ mpt_fetch_disks (int,int*,struct mpt_standalone_disk**) ; 
 int /*<<< orphan*/  mpt_free_pd_list (struct mpt_drive_list*) ; 
 int mpt_open (int) ; 
 struct mpt_drive_list* mpt_pd_list (int) ; 
 int /*<<< orphan*/  mpt_pdstate (TYPE_1__*) ; 
 int mpt_unit ; 
 int /*<<< orphan*/  print_pd (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  print_standalone (struct mpt_standalone_disk*,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
show_drives(int ac, char **av)
{
	struct mpt_drive_list *list;
	struct mpt_standalone_disk *sdisks;
	int error, fd, i, len, nsdisks, state_len;

	if (ac != 1) {
		warnx("show drives: extra arguments");
		return (EINVAL);
	}

	fd = mpt_open(mpt_unit);
	if (fd < 0) {
		error = errno;
		warn("mpt_open");
		return (error);
	}

	/* Get the drive list. */
	list = mpt_pd_list(fd);
	if (list == NULL) {
		error = errno;
		close(fd);
		warn("Failed to get drive list");
		return (error);
	}

	/* Fetch the list of standalone disks for this controller. */
	state_len = 0;
	if (mpt_fetch_disks(fd, &nsdisks, &sdisks) != 0) {
		nsdisks = 0;
		sdisks = NULL;
	}
	if (nsdisks != 0)
		state_len = strlen(STANDALONE_STATE);

	/* Walk the drive list to determine width of state column. */
	for (i = 0; i < list->ndrives; i++) {
		len = strlen(mpt_pdstate(list->drives[i]));
		if (len > state_len)
			state_len = len;
	}

	/* List the drives. */
	printf("mpt%d Physical Drives:\n", mpt_unit);
	for (i = 0; i < list->ndrives; i++) {
		printf("%4u ", list->drives[i]->PhysDiskNum);
		print_pd(list->drives[i], state_len, 1);
		printf("\n");
	}
	mpt_free_pd_list(list);
	for (i = 0; i < nsdisks; i++) {
		printf("%4s ", sdisks[i].devname);
		print_standalone(&sdisks[i], state_len, 1);
		printf("\n");
	}
	free(sdisks);

	close(fd);

	return (0);
}