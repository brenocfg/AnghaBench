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
struct stat {scalar_t__ st_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSD_STABLEBACKUP ; 
 int /*<<< orphan*/  NFSD_STABLERESTART ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  copy_stable (int,int) ; 
 int fstat (int,struct stat*) ; 
 int open (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
open_stable(int *stable_fdp, int *backup_fdp)
{
	int stable_fd, backup_fd = -1, ret;
	struct stat st, backup_st;

	/* Open and stat the stable restart file. */
	stable_fd = open(NFSD_STABLERESTART, O_RDWR, 0);
	if (stable_fd < 0)
		stable_fd = open(NFSD_STABLERESTART, O_RDWR | O_CREAT, 0600);
	if (stable_fd >= 0) {
		ret = fstat(stable_fd, &st);
		if (ret < 0) {
			close(stable_fd);
			stable_fd = -1;
		}
	}

	/* Open and stat the backup stable restart file. */
	if (stable_fd >= 0) {
		backup_fd = open(NFSD_STABLEBACKUP, O_RDWR, 0);
		if (backup_fd < 0)
			backup_fd = open(NFSD_STABLEBACKUP, O_RDWR | O_CREAT,
			    0600);
		if (backup_fd >= 0) {
			ret = fstat(backup_fd, &backup_st);
			if (ret < 0) {
				close(backup_fd);
				backup_fd = -1;
			}
		}
		if (backup_fd < 0) {
			close(stable_fd);
			stable_fd = -1;
		}
	}

	*stable_fdp = stable_fd;
	*backup_fdp = backup_fd;
	if (stable_fd < 0)
		return;

	/* Sync up the 2 files, as required. */
	if (st.st_size > 0)
		copy_stable(stable_fd, backup_fd);
	else if (backup_st.st_size > 0)
		copy_stable(backup_fd, stable_fd);
}