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
struct procstat {int dummy; } ;
struct kinfo_proc {int ki_cr_flags; unsigned int ki_ngroups; int /*<<< orphan*/ * ki_groups; int /*<<< orphan*/  ki_svgid; int /*<<< orphan*/  ki_rgid; int /*<<< orphan*/  ki_svuid; int /*<<< orphan*/  ki_ruid; int /*<<< orphan*/  ki_uid; int /*<<< orphan*/  ki_comm; int /*<<< orphan*/  ki_pid; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int CRED_FLAG_CAPMODE ; 
 int KI_CRF_GRP_OVERFLOW ; 
 int PS_OPT_NOHEADER ; 
 int /*<<< orphan*/  get_umask (struct procstat*,struct kinfo_proc*) ; 
 int /*<<< orphan*/  procstat_freegroups (struct procstat*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * procstat_getgroups (struct procstat*,struct kinfo_proc*,unsigned int*) ; 
 int procstat_opts ; 
 int /*<<< orphan*/  xo_close_list (char*) ; 
 int /*<<< orphan*/  xo_emit (char*,...) ; 
 int /*<<< orphan*/  xo_open_list (char*) ; 

void
procstat_cred(struct procstat *procstat, struct kinfo_proc *kipp)
{
	unsigned int i, ngroups;
	gid_t *groups;

	if ((procstat_opts & PS_OPT_NOHEADER) == 0)
		xo_emit("{T:/%5s %-16s %5s %5s %5s %5s %5s %5s %5s %5s %-15s}\n",
		    "PID", "COMM", "EUID", "RUID", "SVUID", "EGID", "RGID",
		    "SVGID", "UMASK", "FLAGS", "GROUPS");

	xo_emit("{k:process_id/%5d/%d} ", kipp->ki_pid);
	xo_emit("{:command/%-16s/%s} ", kipp->ki_comm);
	xo_emit("{:uid/%5d} ", kipp->ki_uid);
	xo_emit("{:ruid/%5d} ", kipp->ki_ruid);
	xo_emit("{:svuid/%5d} ", kipp->ki_svuid);
	xo_emit("{:group/%5d} ", kipp->ki_groups[0]);
	xo_emit("{:rgid/%5d} ", kipp->ki_rgid);
	xo_emit("{:svgid/%5d} ", kipp->ki_svgid);
	xo_emit("{:umask/%5s} ", get_umask(procstat, kipp));
	xo_emit("{:cr_flags/%s}", kipp->ki_cr_flags & CRED_FLAG_CAPMODE ?
	    "C" : "-");
	xo_emit("{P:     }");

	groups = NULL;
	/*
	 * We may have too many groups to fit in kinfo_proc's statically
	 * sized storage.  If that occurs, attempt to retrieve them using
	 * libprocstat.
	 */
	if (kipp->ki_cr_flags & KI_CRF_GRP_OVERFLOW)
		groups = procstat_getgroups(procstat, kipp, &ngroups);
	if (groups == NULL) {
		ngroups = kipp->ki_ngroups;
		groups = kipp->ki_groups;
	}
	xo_open_list("groups");
	for (i = 0; i < ngroups; i++)
		xo_emit("{D:/%s}{l:groups/%d}", (i > 0) ? "," : "", groups[i]);
	if (groups != kipp->ki_groups)
		procstat_freegroups(procstat, groups);

	xo_close_list("groups");
	xo_emit("\n");
}