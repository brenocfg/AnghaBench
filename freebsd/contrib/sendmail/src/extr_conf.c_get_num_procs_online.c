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
struct pst_dynamic {int psd_proc_cnt; } ;
typedef  int /*<<< orphan*/  psd ;
typedef  int /*<<< orphan*/  nproc ;

/* Variables and functions */
 int CTL_HW ; 
 int HW_NCPU ; 
 int /*<<< orphan*/  _SC_NPROCESSORS_ONLN ; 
 int pstat_getdynamic (struct pst_dynamic*,int,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ sysconf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl (int*,int,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_num_procs_online()
{
	int nproc = 0;

#ifdef USESYSCTL
# if defined(CTL_HW) && defined(HW_NCPU)
	size_t sz;
	int mib[2];

	mib[0] = CTL_HW;
	mib[1] = HW_NCPU;
	sz = (size_t) sizeof(nproc);
	(void) sysctl(mib, 2, &nproc, &sz, NULL, 0);
# endif /* defined(CTL_HW) && defined(HW_NCPU) */
#else /* USESYSCTL */
# ifdef _SC_NPROCESSORS_ONLN
	nproc = (int) sysconf(_SC_NPROCESSORS_ONLN);
# else /* _SC_NPROCESSORS_ONLN */
#  ifdef __hpux
#   include <sys/pstat.h>
	struct pst_dynamic psd;

	if (pstat_getdynamic(&psd, sizeof(psd), (size_t)1, 0) != -1)
		nproc = psd.psd_proc_cnt;
#  endif /* __hpux */
# endif /* _SC_NPROCESSORS_ONLN */
#endif /* USESYSCTL */

	if (nproc <= 0)
		nproc = 1;
	return nproc;
}