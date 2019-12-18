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
struct statfs {int f_bfree; int f_blocks; } ;
struct dir_ent {char softlim; char hardlim; char* dirname; } ;

/* Variables and functions */
 int ADE_HARDLIM ; 
 int ADE_NOMEM ; 
 int ADE_SOFTLIM ; 
 int AUDIT_HARD_LIMIT_FREE_BLOCKS ; 
 int MAXNAMLEN ; 
 int auditd_hostlen ; 
 int auditd_minval ; 
 int /*<<< orphan*/  auditd_set_host () ; 
 int auditd_set_minfree () ; 
 int /*<<< orphan*/  endac () ; 
 int /*<<< orphan*/  free (struct dir_ent*) ; 
 int /*<<< orphan*/  free_dir_q () ; 
 scalar_t__ getacdir (char*,int) ; 
 int /*<<< orphan*/  insert_orderly (struct dir_ent*) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ statfs (char*,struct statfs*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int stub1 (char*) ; 
 int stub2 (char*) ; 

int
auditd_read_dirs(int (*warn_soft)(char *), int (*warn_hard)(char *))
{
	char cur_dir[MAXNAMLEN];
	struct dir_ent *dirent;
	struct statfs sfs;
	int err;
	char soft, hard;
	int tcnt = 0;
	int scnt = 0;
	int hcnt = 0;

	if (auditd_minval == -1 && (err = auditd_set_minfree()) != 0)
		return (err);

	if (auditd_hostlen == -1)
		auditd_set_host();

	/*
	 * Init directory q.  Force a re-read of the file the next time.
	 */
	free_dir_q();
	endac();

	/*
	 * Read the list of directories into an ordered linked list
	 * admin's preference, then those over soft limit and, finally,
	 * those over the hard limit.
	 *
	 * XXX We should use the reentrant interfaces once they are
	 * available.
	 */
	while (getacdir(cur_dir, MAXNAMLEN) >= 0) {
		if (statfs(cur_dir, &sfs) < 0)
			continue;  /* XXX should warn */
		soft = (sfs.f_bfree < (sfs.f_blocks * auditd_minval / 100 )) ?
		    1 : 0;
		hard = (sfs.f_bfree < AUDIT_HARD_LIMIT_FREE_BLOCKS) ? 1 : 0;
		if (soft) {
			if (warn_soft)
				(*warn_soft)(cur_dir);
			scnt++;
		}
		if (hard) {
			if (warn_hard)
				(*warn_hard)(cur_dir);
			hcnt++;
		}
		dirent = (struct dir_ent *) malloc(sizeof(struct dir_ent));
		if (dirent == NULL)
			return (ADE_NOMEM);
		dirent->softlim = soft;
		dirent->hardlim = hard;
		dirent->dirname = (char *) malloc(MAXNAMLEN);
		if (dirent->dirname == NULL) {
			free(dirent);
			return (ADE_NOMEM);
		}
		strlcpy(dirent->dirname, cur_dir, MAXNAMLEN);
		insert_orderly(dirent);
		tcnt++;
	}

	if (hcnt == tcnt)
		return (ADE_HARDLIM);
	if (scnt == tcnt)
		return (ADE_SOFTLIM);
	return (0);
}