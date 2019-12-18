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
struct ptsstat {int dummy; } ;
struct procstat {scalar_t__ type; int /*<<< orphan*/  kd; } ;
struct filestat {int dummy; } ;

/* Variables and functions */
 scalar_t__ PROCSTAT_CORE ; 
 scalar_t__ PROCSTAT_KVM ; 
 scalar_t__ PROCSTAT_SYSCTL ; 
 int /*<<< orphan*/  _POSIX2_LINE_MAX ; 
 int /*<<< orphan*/  assert (struct ptsstat*) ; 
 int procstat_get_pts_info_kvm (int /*<<< orphan*/ ,struct filestat*,struct ptsstat*,char*) ; 
 int procstat_get_pts_info_sysctl (struct filestat*,struct ptsstat*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  warnx (char*,scalar_t__) ; 

int
procstat_get_pts_info(struct procstat *procstat, struct filestat *fst,
    struct ptsstat *pts, char *errbuf)
{

	assert(pts);
	if (procstat->type == PROCSTAT_KVM) {
		return (procstat_get_pts_info_kvm(procstat->kd, fst, pts,
		    errbuf));
	} else if (procstat->type == PROCSTAT_SYSCTL ||
		procstat->type == PROCSTAT_CORE) {
		return (procstat_get_pts_info_sysctl(fst, pts, errbuf));
	} else {
		warnx("unknown access method: %d", procstat->type);
		if (errbuf != NULL)
			snprintf(errbuf, _POSIX2_LINE_MAX, "error");
		return (1);
	}
}