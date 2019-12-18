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
typedef  int u_short ;
struct procstat {int dummy; } ;
struct kinfo_proc {int dummy; } ;

/* Variables and functions */
 scalar_t__ procstat_getumask (struct procstat*,struct kinfo_proc*,int*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static const char *
get_umask(struct procstat *procstat, struct kinfo_proc *kipp)
{
	u_short fd_cmask;
	static char umask[4];

	if (procstat_getumask(procstat, kipp, &fd_cmask) == 0) {
		snprintf(umask, 4, "%03o", fd_cmask);
		return (umask);
	} else {
		return ("-");
	}
}